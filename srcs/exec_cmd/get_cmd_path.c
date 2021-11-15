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

static void	print_if_error(char *path, char *name, t_shell *shell)
{
	if (path == NULL)
	{
		ft_printf_fd(2, "%s: %s: command not found\n", \
		PROMPTERR, name);
	}
	else if (shell->ret > 0)
		print_error_prompt(path);
}

static int	path_exist(char *path, t_cmd *cmd, t_shell *shell)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		if (cmd->path != NULL)
			free(cmd->path);
		cmd->path = ft_strdup(path);
		if (access(path, X_OK) != 0)
		{
			shell->ret = 126;
			return (0);
		}
		close_perror(fd);
		shell->ret = 0;
		return (1);
	}
	shell->ret = 127;
	return (0);
}

int	is_path_and_xok(char *path)
{
	int	fd;
	int	ret;

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

/*
 * Will go through every path to check if the command exist,
 * if it exist but not X_OK, it will set the error return
 * and continue to search
 */
static void	browse_tab(char **path_tab, t_shell *shell)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], *shell->cmd->param);
		if (path == NULL)
			return ;
		if (path_exist(path, shell->cmd, shell))
		{
			free(path);
			break ;
		}
		i++;
		free(path);
	}
	ft_free_str_tab(path_tab);
}

/*
 * This function will seek the cmd path and check if it can
 * be executed
 */
int	get_cmd_path(t_shell *shell, char **path_tab)
{
	t_env	*env;

	env = shell->env;
	if (is_absolute_path(shell, path_tab))
		return (shell->ret);
	else if (path_tab == NULL || \
	(env_seeker(&env, "PATH") && !env->value) || \
	!*env->value)
	{
		shell->cmd->path = ft_strdup(*shell->cmd->param);
		return (is_path_and_xok(*shell->cmd->param));
	}
	else
		browse_tab(path_tab, shell);
	print_if_error(shell->cmd->path, *shell->cmd->param, shell);
	return (shell->ret);
}
