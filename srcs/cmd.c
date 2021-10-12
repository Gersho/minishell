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
		path = ft_strjoin(path_tab[i++], cmd->param);
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
	if (command_not_found(cmd->path, cmd->param))
		return (-1);//free and exit
	return (0);
}
int exec_cmd(t_list *cmd, char **env)
{
	char **path_tab;
	int pid;

	path_tab = split_env_path(env);
	while (cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{

			get_cmd_path(cmd->param);//just before execve
		}
		else if (pid == -1)
			return (-1);//perror fork
		cmd = cmd->next;
	}
}