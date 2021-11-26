/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:41:53 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/25 12:59:50 by kzennoun         ###   ########lyon.fr   */
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

static void	dup_std_and_dup2(t_shell *shell)
{
	shell->std_in = dup(0);
	shell->std_out = dup(1);
	if (shell->std_in == -1 || shell->std_out == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}
	redirect_handler(shell);
	replace_std(shell->cmd->in, shell->cmd->out);
	shell->cmd->in = 0;
}

/*
 * Check what builtin it is, launch it and retrieve the return
 */
static int	what_cmd(int command, t_shell *shell, int in_fork)
{
	if (!in_fork)
		dup_std_and_dup2(shell);
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
