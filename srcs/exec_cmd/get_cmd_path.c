/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:03 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:04 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	command_not_found(char *path, char *name)
{
	if (path == NULL)
	{
		ft_printf_fd(2, "%s: %s: command not found\n", \
		PROMPTERR, name);
		return (127);
	}
	return (0);
}

static int	path_exist(char *path, t_cmd *cmd)
{
	int	fd;
	int	ret;

	ret = 0;
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		if (cmd->path != NULL)
			free(cmd->path);
		cmd->path = ft_strdup(path);
		if (access(path, X_OK) != 0)
			ret = 126;
		close_perror(fd);
	}
	return (ret);
}

static int	is_absolute_path(t_shell *shell, char **path_tab)
{
	int	fd;

	if (**shell->cmd->param == '/' || **shell->cmd->param == '.')
	{
		ft_free_str_tab(path_tab);
		shell->cmd->path = ft_strdup(*shell->cmd->param);
		fd = open(shell->cmd->path, O_RDONLY);
		if (fd == -1)
		{
			print_error_prompt(shell->cmd->path);
			shell->ret = 127;
		}
		else if (access(shell->cmd->path, X_OK) != 0)
		{
			print_error_prompt(shell->cmd->path);
			shell->ret = 126;
		}
		if (fd != -1)
			close_perror(fd);
		return (1);
	}
	return (0);
}

int	get_cmd_path(t_shell *shell, char **path_tab)
{
	int		i;
	char	*path;
	t_env	*env;

	env = shell->env;
	i = 0;
	path = NULL;
	if (is_absolute_path(shell, path_tab))
		return (shell->ret);
	else if (path_tab == NULL || (env_seeker(&env, "PATH") && !env->value))
	{
		int fd = open(*shell->cmd->param, O_RDONLY);
		if (fd == -1)
		{
			print_error_prompt(*shell->cmd->param);
			return (127);
		}
		if (access(*shell->cmd->param, X_OK) != 0)
		{
			print_error_prompt(*shell->cmd->param);
			return (126);
		}
	}
	else
	{
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
	}
	return (command_not_found(shell->cmd->path, *shell->cmd->param));
}
