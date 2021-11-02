//
// Created by Johan Chevet on 10/14/21.
//

#include "../headers/minishell.h"

static int	command_not_found(char *path, char *name)
{
	if (path == NULL)
	{
		ft_printf_fd(2, "%s%s%s: %s: command not found\n", KRED, PROMPTERR, KNRM, name);//TODO need prompt str
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

int	get_cmd_path(t_shell *shell, char **path_tab)
{
	int		i;
	char	*path;
	int fd;
	
	i = 0;
	path = NULL;
	if (**shell->cmd->param == '/' || **shell->cmd->param == '.')
	{
		ft_free_str_tab(path_tab);
		shell->cmd->path = *shell->cmd->param;
		fd = open(shell->cmd->path, O_RDONLY);
		if (fd == -1)
		{
			perror(shell->cmd->path);
			return (127);
		}
		close (fd);
		if (access(shell->cmd->path, X_OK))
		{
			perror(shell->cmd->path);
			return (126);
		}
		return (0);
	}
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], *shell->cmd->param);
		if (path == NULL)
			return (1);
		if (path_exist(path, shell->cmd))
		{
			free(path);
			break;
		}
		i++;
		free(path);
	}
	ft_free_str_tab(path_tab);
	if (command_not_found(shell->cmd->path, *shell->cmd->param))
		return (127);
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

	paths_tab = NULL;
	env_seeker(&env, "PATH");
	if (env)
	{
		paths_tab = ft_split(env->value, ':');
		if (paths_tab == NULL)
			exit(EXIT_FAILURE);
		add_slash_to_path(paths_tab);
	}
	return (paths_tab);
}