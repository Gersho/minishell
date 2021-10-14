//
// Created by Johan Chevet on 10/12/21.
//

#include "../headers/token.h"
#include "../libft/include/libft.h"

int	add_slash_to_path(char **path_tab)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		if (!tmp)
		{
			ft_free_str_tab(path_tab);
			return (-1);
		}
		free(path_tab[i]);
		path_tab[i] = tmp;
		i++;
	}
	return (1);
}

char	**split_env_path(char **envp)
{
	int		i;
	char	**paths_tab;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	envp[i] += 5;
	paths_tab = ft_split(envp[i], ':');
	if (paths_tab == NULL)
		exit(EXIT_FAILURE);
	add_slash_to_path(paths_tab);
	return (paths_tab);
}

int	path_exist(char *path, t_cmd *cmd)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		if (cmd->path != NULL)
			free(cmd->path);
		cmd->path = ft_strdup(path);
		if (cmd->path == NULL)
			return (-1);
		if (access(path, X_OK) == 0)//test with path == NULL for possible crash
		{
			close(fd);//check if failed?
			return (1);
		}
		else
		{
			close(fd);
			return (0);
		}
	}
	return (0);
}

int	command_not_found(char *path, char *name)
{
	if (path == NULL)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

int	get_cmd_path(t_cmd *cmd, char **path_tab)
{
	int		i;
	char	*path;

	i = 0;
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i++], cmd->param->str);
		if (path == NULL)
			return (-1);//free path_tab and exit
		if (path_exist(path, cmd) == 1)
		{
			free(path);
			break ;
		}
		free(path);
	}
	ft_free_str_tab(path_tab);
	if (command_not_found(cmd->path, cmd->param->str))
		return (-1);//free and exit
	return (0);
}

char **list_to_tab(t_args *p_list)
{
	char **p_tab;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_size_list(p_list);
	p_tab = ft_calloc(size + 1, sizeof(char*));
	if (!p_tab)
		return (NULL);
	while (i < size)
	{
		p_tab[i] = ft_strdup(p_list->str);
		//if p_tab[i] == NULL free
		i++;
		p_list = p_list->next;
	}
	return (p_tab);
}

int skip_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

int is_redirect(char c)
{
	if (c == '>' || c == '<')//more to come
		return (1);
	return (0);
}

char *get_filename(char *str)
{
	char	*filename;
	size_t i;

	i = 0;
	while (str[i] && !is_redirect(str[i]))
		i++;
	filename = malloc(sizeof(char) * (i + 1));
	if (filename == NULL)
		return (NULL);
	ft_strlcpy(filename, str, i + 1);
	return (filename);
}

int open_with_param(char *filename, int redirect_mode, int mode)
{
	int 	file_fd;

	if (redirect_mode == RED_OUT_T)
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	else if (redirect_mode == RED_OUT_A)
		file_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00644);
	else if (redirect_mode == RED_IN)
		file_fd = open(filename, O_RDWR, S_IRWXU | S_IRWXG);
	if (file_fd == -1) {
		perror("open");
		return (0);
	}
	if (mode == STDOUT_FILENO)
		dup2(file_fd , STDOUT_FILENO);//TODO close fd at every call of dup2
	else {
	ft_putstr_nl_fd(filename, 1);
		dup2(file_fd, STDIN_FILENO);
		char *line;
		get_next_line(0, &line);
		ft_putstr_nl_fd(line, 1);
	}
	return (1);
}

int	redirect_handler(char *red)
{
	int		mode;
	int 	redirect_mode;
	char	*filename;

	mode = 0;
	redirect_mode = 0;
	while (*red)
	{
		if (*red == '>')
		{
			mode = STDOUT_FILENO;
			if (*(red + 1) == '>')
			{
				redirect_mode = RED_OUT_A;
				red++;
			}
			else
				redirect_mode = RED_OUT_T;
		}
		else if (*red == '<')
		{
			mode = STDIN_FILENO;
			if (*(red + 1) == '<')
				redirect_mode = HERE_DOC;
			else
				redirect_mode = RED_IN;
		}
		red++;
		red += skip_spaces(red);
		filename = get_filename(red);
		if (filename == NULL)
			return (-1);
		red += ft_strlen(filename);
		open_with_param(filename, redirect_mode, mode); //close fd if more redirect
	}
	return (1);
}

int exec_cmd(t_cmd *cmd, char **env)
{
	char **path_tab;
	int pid;
	int pipe_fd[2];
	int std_out;
	int std_in;
	int i = 0;
	path_tab = split_env_path(env);
	std_out = dup(1);
	std_in = dup(0);
	int	prev_pipe_r;
	while (cmd != NULL)
	{
		if (pipe(pipe_fd) == -1)
			perror("pipe");
		if (i > 0)
			dup2(prev_pipe_r, 0);
		if (cmd->next)//if there is a pipe
			dup2(pipe_fd[1], 1);
		else
			dup2(std_out, 1);
		pid = fork();
		if (pid == 0)
		{
			cmd->param_tab = list_to_tab(cmd->param);
			if (cmd->red)
				redirect_handler(cmd->red->str);
			get_cmd_path(cmd, path_tab);
			ft_putstr_nl_fd(cmd->param_tab[0], std_out);
//			char *line;
//			get_next_line(0, &line);
//			ft_putstr_nl_fd(line, std_out);
			execve(cmd->path, cmd->param_tab, env);
			perror("execve");
		}
		else if (pid == -1)
			return (-1);//perror fork
		if (cmd->next)
			prev_pipe_r = dup(pipe_fd[0]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		cmd = cmd->next;
		i++;
	}
	if (i > 1)
		close(prev_pipe_r);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_cmd *cmd;

	cmd = ft_cmd_init();
	
	
	
	
	
	cmd = malloc(sizeof(t_cmd));
	cmd->param = malloc(sizeof(t_args));
	cmd->param->str = ft_strdup("ls");
	cmd->param->next = NULL;
	cmd->red = NULL;
	cmd->param->next = malloc(sizeof(t_args));
	cmd->param->next->str = ft_strdup("-la");
	cmd->param->next->next = NULL;
//	cmd->red = malloc(sizeof(t_args));
//	cmd->red->str = ft_strdup("> test.txt");
//	cmd->red->next = NULL; //useless atm
	cmd->path = NULL;
	cmd->param_tab = NULL;

	//next cmd
	cmd->next = NULL;
	cmd->next = malloc(sizeof(t_cmd));
	cmd->next->next = NULL;
	cmd->next->red = NULL;
	cmd->next->red = malloc(sizeof(t_args));
	cmd->next->red->str = ft_strdup("< test.txt");
	cmd->next->param = malloc(sizeof(t_args));
	cmd->next->param->str = ft_strdup("cat");
	cmd->next->param->next = NULL;
//	cmd->next->param->next = malloc(sizeof(t_args));
//	cmd->next->param->next->str = ft_strdup("");
//	cmd->next->param->next->next = NULL;
	cmd->next->path = NULL;
	cmd->next->param_tab = NULL;
//	printf("cmd->param->str %s\n", cmd->param->str);
	exec_cmd(cmd, env);
	wait(NULL);
}