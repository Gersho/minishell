/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:41:49 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:41:50 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * Will replace cmd->in and cmd->out by pipe if there is no heredoc
 */
static void	set_cmd_in_and_out(t_shell *shell, int *pipe_fd, int first)
{
	if (!first)
	{
		if (shell->cmd->in != 0)
			close_perror(pipe_fd[0]);
		else
			shell->cmd->in = pipe_fd[0];
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	if (shell->cmd->next)
		shell->cmd->out = pipe_fd[1];
	else
		close_multiple_fd(2, pipe_fd[0], pipe_fd[1]);
}

void	launch_all_commands(t_shell *shell, int *status)
{
	int	first;
	int	pipe_fd[2];

	first = 1;
	while (shell->cmd)
	{
		if (first && !shell->cmd->next && is_built_in(*shell->cmd->param))
		{
			exec_built_in(shell, 0);
			*status = -1;
		}
		else
		{
			set_cmd_in_and_out(shell, pipe_fd, first);
			exec_cmd_fork(shell, pipe_fd[0]);
		}
		if (shell->cmd->next)
			close_perror(pipe_fd[1]);
		if (shell->cmd->in != 0)
			close_perror(shell->cmd->in);
		shell->cmd = shell->cmd->next;
		first = 0;
	}
}
