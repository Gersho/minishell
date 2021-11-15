/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:09 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:10 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	last_pid(t_cmd *cmd)
{
	cmd = ft_cmd_last(cmd);
	return (cmd->pid);
}

static void	wait_all_process(t_cmd *cmd, t_shell *shell)
{
	int	status;
	int	nl;

	nl = 0;
	waitpid(last_pid(cmd), &status, 0);
	if (WIFSIGNALED(status))
	{
		nl = 1;
		if (WTERMSIG(status) == SIGINT)
			shell->ret = 130;
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3", 2);
			shell->ret = 131;
		}
	}
	else
		shell->ret = WEXITSTATUS(status);
	while (waitpid(cmd->pid, &status, 0) != -1)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
			nl = 1;
		cmd = cmd->next;
	}
	if (nl == 1)
		write(1, "\n", 1);
}

static int	check_heredoc(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;

	cmd = shell->cmd;
	while (cmd)
	{
		i = -1;
		if (cmd->red)
		{
			while (cmd->red[++i])
			{
				if (which_redirect(cmd->red[i]) != HERE_DOC)
					continue ;
				if (!here_doc(cmd->red[i + 1], shell))
					return (0);
			}
		}
		cmd = cmd->next;
	}
	return (1);
}

void	parse_cmd(t_shell *shell)
{
	int		status;
	t_cmd	*cmd_ptr;

	status = 0;
	shell->error = 0;
	cmd_ptr = shell->cmd;
	if (check_heredoc(shell))
	{
		redirect_handler(shell);
		if (!shell->error)
			launch_all_commands(shell, &status);
		else
		{
			close_all_fds(shell);
			shell->ret = EXIT_FAILURE;
		}
		if (status != -1 && !shell->error)
			wait_all_process(cmd_ptr, shell);
	}
	free_cmd_list(cmd_ptr);
	shell->cmd = NULL;
}
