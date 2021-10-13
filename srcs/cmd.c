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

int open_with_param(char *filename, int open_param)
{
	int 	file_fd;

	if (open_param == RED_OUT_T)
	{
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	}
	else if (open_param == RED_OUT_A)
		file_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00644);
	if (file_fd == -1) {
		perror("open");
		return (0);
	}
	dup2(file_fd , 1);
	return (1);
}

int	redirect_handler(char *red)
{
	size_t	i;
	int 	open_param;
	char	*filename;

	i = 0;
	open_param = 0;
	while (*red)
	{
		if (*red == '>')
		{
			if (*(red + 1) == '>')
			{
				open_param = RED_OUT_A;
				red++;
			}
			else
				open_param = RED_OUT_T;
		}
		red++;
		red += skip_spaces(red);
		filename = get_filename(red);
		if (filename == NULL)
			return (-1);
		red += ft_strlen(filename);
		open_with_param(filename, open_param);
	}
	return (1);
}

int exec_cmd(t_cmd *cmd, char **env)
{
	char **path_tab;
	int pid;
	int pipe_fd[2];

	path_tab = split_env_path(env);
	while (cmd != NULL)
	{
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
				perror("pipe");
			dup2(pipe_fd[1], 1);
		}
		pid = fork();
		if (pid == 0)
		{
			cmd->param_tab = list_to_tab(cmd->param);
			if (cmd->red) {
				redirect_handler(cmd->red->str);
			}
			get_cmd_path(cmd, path_tab);//just before execve
			execve(cmd->path, cmd->param_tab, env);
			perror("execve");
		}
		else if (pid == -1)
			return (-1);//perror fork
		cmd = cmd->next;
	}
	return (1);
}
//
//int main(int ac, char **av, char **env)
//{
//	t_cmd *cmd;
//
////	cmd = ft_cmd_init();
//	cmd = malloc(sizeof(t_cmd));
//	cmd->next = NULL;
//	cmd->param = malloc(sizeof(t_args));
//	cmd->param->str = ft_strdup("ls");
//	cmd->param->next = malloc(sizeof(t_args));
//	cmd->param->next->str = ft_strdup("-l");
//	cmd->param->next->next = NULL;
//	cmd->red = malloc(sizeof(t_args));
//	cmd->red->str = ft_strdup(">> test1.txt");
//	cmd->red->next = NULL; //useless atm
////	cmd->red = NULL;
//	cmd->path = NULL;
//	cmd->param_tab = NULL;
////	printf("cmd->param->str %s\n", cmd->param->str);
//	exec_cmd(cmd, env);
//	wait(NULL);
//}