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

static int	path_exist(char *path, t_cmd *cmd, t_shell *shell, char **denied)
{
	struct stat	stat_path;

	if (stat(path, &stat_path) == -1)
	{
		shell->ret = 127;
		return (0);
	}
	if (cmd->path != NULL)
		free(cmd->path);
	cmd->path = ft_strdup(path);
	if (access(path, X_OK) != 0)
	{
		if (*denied == NULL)
			*denied = ft_strdup(cmd->path);
		shell->ret = 126;
		return (0);
	}
	shell->ret = 0;
	return (1);
}

/*
 * Verify if there is something in path, if it is a directory,
 * if it can be executed and set the return value
 */
int	is_path_and_xok(char *path)
{
	struct stat	stat_path;
	int			ret;

	ret = 0;
	if (stat(path, &stat_path) == -1)
	{
		print_error_prompt(path);
		return (127);
	}
	if (S_ISDIR(stat_path.st_mode))
	{
		ft_printf_fd(2, "%s: %s: is a directory\n", PROMPTERR, path);
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		print_error_prompt(path);
		ret = 126;
	}
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
	char	*denied;
	int		i;

	i = -1;
	path = NULL;
	denied = NULL;
	while (path_tab[++i])
	{
		path = ft_strjoin(path_tab[i], *shell->cmd->param);
		if (path == NULL)
			return ;
		if (path_exist(path, shell->cmd, shell, &denied))
		{
			free(path);
			break ;
		}
		free(path);
	}
	if (shell->cmd->path != NULL && shell->ret == 126)
	{
		free(shell->cmd->path);
		shell->cmd->path = denied;
	}
	ft_free_str_tab(path_tab);
}

/*
 * This function will seek the cmd path and check if it can
 * be executed
 */
int	get_cmd_path(t_shell *shell)
{
	t_env	*env;
	char	**path_tab;

	env = shell->env;
	if (is_absolute_path(shell))
		return (shell->ret);
	path_tab = split_env_path(shell->env);
	if (path_tab == NULL || \
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
