/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:29 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:30 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	wait_process(t_shell *shell, int pid, int *pipe_doc)
{
	int	status;
	
	waitpid(pid, &status, 0);
	close_perror(pipe_doc[1]);
	shell->cmd->in = pipe_doc[0];
	if (WIFSIGNALED(status))
	{
		ft_putchar_fd('\n', 2);
		shell->ret = 1;
		return (0);
	}
	shell->ret = WEXITSTATUS(status);
	return (1);
}

int	here_doc(char *limiter, t_shell *shell)
{
	char	*line;
	int		pipe_doc[2];
	int 	pid;

	//todo readline
	if (pipe(pipe_doc) == -1)
		perror("pipo");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close_perror(pipe_doc[0]);
		ft_printf_fd(1, "%s> %s", KMAG, KNRM);
		while (get_next_line(0, &line))
		{
			if (ft_strcmp(limiter, line) == 0)
			{
				free(line);
				close_perror(pipe_doc[1]);
				exit(EXIT_SUCCESS);
			}
			ft_printf_fd(1, "%s> %s", KMAG, KNRM);
			ft_putstr_nl_fd(line, pipe_doc[1]);
			free(line);
		}
		free(line);
		close_perror(pipe_doc[1]);
		exit(EXIT_SUCCESS);
	}
	return (wait_process(shell, pid, pipe_doc));
}



