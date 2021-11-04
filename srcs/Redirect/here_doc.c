//
// Created by Stellar on 14/10/2021.
//

#include "../../headers/minishell.h"

int	here_doc(char *limiter, t_cmd *cmd)
{
	char	*line;
	int		pipe_doc[2];

	if (pipe(pipe_doc) == -1)
		perror("pipo");
	ft_printf_fd(1, "%s> %s", KMAG, KNRM);
	get_next_line(0, &line);
	while (ft_strcmp(limiter, line) != 0)
	{
		ft_printf_fd(1, "%s> %s", KMAG, KNRM);
		ft_putstr_nl_fd(line, pipe_doc[1]);
		free(line);
		get_next_line(0, &line);
	}
	free(line);
	close_perror(pipe_doc[1]);
	dup2_close(pipe_doc[0], cmd->in);
	return (1);
}
