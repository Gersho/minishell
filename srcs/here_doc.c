//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

//TODO func that close fds with unknown nb of param??
int here_doc(char* limiter, t_cmd *cmd)
{
	char*	line;
	int 	pid;
	int 	pipo[2];
	
	if (pipe(pipo) == -1)
		perror("pipo");
//	ft_putstr_fd(limiter, 2);
//	ft_putstr_nl_fd("%", 2);
	pid = fork();
	if (pid == 0)
	{
		close_fds( 2, cmd->fd->pipe[0], pipo[0]);
		ft_putstr_fd("> ", cmd->fd->std_out);
		get_next_line(cmd->fd->std_in, &line);
		while (ft_strcmp(limiter, line) != 0)
		{
			ft_putstr_fd("> ", cmd->fd->std_out);
			ft_putstr_nl_fd(line, pipo[1]);
			free(line);
			get_next_line(cmd->fd->std_in, &line);
		}
		close_fds(3, pipo[1], cmd->fd->std_in, cmd->fd->std_out);
		free(line);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	close_perror(pipo[1]);
	dup2_close(pipo[0], 0);
	return (1);
}