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

static int is_path_and_xok(char *path)
{
	int fd;
	int ret;

	ret = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error_prompt(path);
		ret = 127;
	}
	else if (access(path, X_OK) != 0)
	{
		print_error_prompt(path);
		ret = 126;
	}
	if (fd != -1)
		close_perror(fd);
	return (ret);
}

static int	is_absolute_path(t_shell *shell, char **path_tab)
{
	if (**shell->cmd->param == '/' || **shell->cmd->param == '.')
	{
		ft_free_str_tab(path_tab);
		shell->cmd->path = ft_strdup(*shell->cmd->param);
		shell->ret = is_path_and_xok(shell->cmd->path);
		return (1);
	}
	return (0);
}

static void	browse_tab(char **path_tab, t_shell *shell)
{
	char	*path;
	int 	i;

	i = 0;
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], *shell->cmd->param);
		if (path == NULL)
			return ;
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

int	get_cmd_path(t_shell *shell, char **path_tab)
{
	t_env	*env;

	env = shell->env;
	if (is_absolute_path(shell, path_tab))
		return (shell->ret);
	else if (path_tab == NULL || (env_seeker(&env, "PATH") && !env->value))
	{
		shell->cmd->path = ft_strdup(*shell->cmd->param);
		return (is_path_and_xok(*shell->cmd->param));
	}
	else
		browse_tab(path_tab, shell);
	return (command_not_found(shell->cmd->path, *shell->cmd->param));
}
