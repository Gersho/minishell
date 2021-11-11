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

void sig_doc(int sig)
{
	(void)sig;
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

int	here_doc(char *limiter, t_shell *shell)
{
	char	*line;
	int		pipe_doc[2];
	int 	pid;
	int 	status;

	if (pipe(pipe_doc) == -1)
		perror("pipo");
	pid = fork();
	if (pid == 0)
	{
//		close_perror(pipe_doc[0]);
//		while (1)
//		{
//			line = readline("\x1B[35m> \x1B[0m");
//			if (!line)
//				exit(EXIT_SUCCESS);
//			if (ft_strcmp(limiter, line) == 0) {
//				free(line);
//				break;
//			}
//			ft_putstr_nl_fd(line, pipe_doc[1]);
//			free(line);
//		}
		printf("limiter=%s\n", limiter);
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
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		shell->ret = 1;
	}
	close_perror(pipe_doc[1]);
	shell->cmd->in = pipe_doc[0];
//	dup2_close(pipe_doc[0], shell->cmd->in);
	return (1);
}



