//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

//TODO func that close fds with unknown nb of param??
int here_doc(char* limiter, t_cmd *cmd)
{
	int		len;
	char*	line;
	int 	pid;
	int 	pipo[2];
	
	pipe(pipo);
	ft_putstr_fd(limiter, 2);
	ft_putstr_nl_fd("%", 2);
	pid = fork();
	if (pid == 0)
	{
		close (cmd->fd->std_out);
		close (cmd->fd->pipe[0]);
		close (cmd->fd->pipe[1]);
		close (pipo[0]);
		len = ft_strlen(limiter);
		get_next_line(cmd->fd->std_in, &line);
		while (ft_strncmp(limiter, line, len) != 0)
		{
			ft_putstr_nl_fd(line, pipo[1]);
			free(line);
			get_next_line(cmd->fd->std_in, &line);
		}
		close (cmd->fd->pipe[1]);
		close (cmd->fd->std_in);
		free(line);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	close (pipo[1]);
	dup2_close(pipo[0], 0);
	return (1);
}