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

void	launch_all_commands(t_shell *shell, int *status)
{
	int	first;
	int pipe_fd[2];

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
			if (!first)
				shell->cmd->in = pipe_fd[0];
			pipe(pipe_fd);
			if (shell->cmd->next)
				shell->cmd->out = pipe_fd[1];
			else
				close_multiple_fd(2, pipe_fd[0], pipe_fd[1]);
			exec_cmd_fork(shell, pipe_fd[0]);
		}
		if (shell->cmd->next)
			close_perror(pipe_fd[1]);
		if (!first)
			close_perror(shell->cmd->in);
		shell->cmd = shell->cmd->next;
		first = 0;
	}
}
