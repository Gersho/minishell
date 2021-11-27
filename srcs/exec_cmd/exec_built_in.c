/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:41:53 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/27 13:35:48 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_built_in(char *param)
{
	char		*name;
	t_cmd_name	cmd;

	cmd = NOT_BUILT_IN_M;
	name = str_in_lower_case(param);
	if (name == NULL)
		return (0);
	if (ft_strcmp("echo", name) == 0)
		cmd = ECHO_M;
	else if (ft_strcmp("pwd", name) == 0)
		cmd = PWD_M;
	else if (ft_strcmp("cd", name) == 0)
		cmd = CD_M;
	else if (ft_strcmp("env", name) == 0)
		cmd = ENV_M;
	else if (ft_strcmp("export", param) == 0)
		cmd = EXPORT_M;
	else if (ft_strcmp("unset", param) == 0)
		cmd = UNSET_M;
	else if (ft_strcmp("exit", param) == 0)
		cmd = EXIT_M;
	free(name);
	return (cmd);
}

/*
 * This will save std in and out then do the the redirect if there is one/many
 */
static void	redirect_in_main(t_shell *shell)
{
	if (*shell->cmd->red)
	{
		shell->std_in = dup(0);
		if (shell->std_in == -1)
			free_all(shell, 1, "dup");
		shell->std_out = dup(1);
		if (shell->std_out == -1)
			free_all(shell, 1, "dup");
		redirect_handler(shell);
	}
}

/*
 * Check what builtin it is, launch it and retrieve the return
 */
static int	what_cmd(int command, t_shell *shell, int in_fork)
{
	if (!in_fork)
		redirect_in_main(shell);
	if (!shell->error)
	{
		if (command == ECHO_M)
			shell->ret = echo(shell->cmd->param);
		else if (command == PWD_M)
			shell->ret = pwd();
		else if (command == CD_M)
			shell->ret = cd(shell->cmd->param, shell->env);
		else if (command == ENV_M)
			shell->ret = env(shell->env);
		else if (command == EXPORT_M)
			shell->ret = export(shell->cmd->param, &shell->env);
		else if (command == UNSET_M)
			shell->ret = unset(shell->cmd->param, &shell->env);
		else
			exit_shell(shell, in_fork);
	}
	if (!in_fork)
		replace_std(shell->std_in, shell->std_out);
	shell->std_in = 0;
	shell->std_out = 1;
	return (1);
}

int	exec_built_in(t_shell *shell, int in_fork)
{
	int	command;

	if (*shell->cmd->param)
	{
		command = is_built_in(*shell->cmd->param);
		if (command != NOT_BUILT_IN_M)
			return (what_cmd(command, shell, in_fork));
	}
	return (0);
}
