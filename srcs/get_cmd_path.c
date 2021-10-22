//
// Created by Johan Chevet on 10/14/21.
//

#include "../headers/minishell.h"

static int	command_not_found(char *path, char *name)
{
	if (path == NULL)
	{
		dprintf(2, "%s%s: command not found\n", PROMPT, name);
//		ft_putstr_fd(name, 2);
//		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

static int	path_exist(char *path, t_cmd *cmd)
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
			close_perror(fd);
			return (1);
		}
		else
		{
			close_perror(fd);
			return (0);
		}
	}
	return (0);
}

int	get_cmd_path(t_cmd *cmd, char **path_tab)
{
	int		i;
	char	*path;
	
	i = 0;
	if (**cmd->param == '/')
	{
		ft_free_str_tab(path_tab);
		cmd->path = *cmd->param;
		return (0);
	}
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], *cmd->param);
		if (path == NULL)
			return (-1);//TODO free path_tab and exit
		if (path_exist(path, cmd) == 1)
		{
			free(path);
			break ;
		}
		i++;
		free(path);
	}
	ft_free_str_tab(path_tab);
	if (command_not_found(cmd->path, *cmd->param))
		exit (-1);//TODO free and exit
	return (0);
}

static int	add_slash_to_path(char **path_tab)
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

char	**split_env_path(t_env *env)
{
	char	**paths_tab;
	t_env 	*path;
	//TODO what if path is deleted
	path = env_seeker(env, "PATH");
	paths_tab = ft_split(path->value, ':');
	if (paths_tab == NULL)
		exit(EXIT_FAILURE);
	add_slash_to_path(paths_tab);
	return (paths_tab);
}