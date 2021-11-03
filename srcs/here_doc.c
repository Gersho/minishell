//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

int here_doc(char *limiter, t_cmd *cmd)
{
	char*	line;
	int 	pipo[2];

	if (pipe(pipo) == -1)
		perror("pipo");
	ft_printf_fd(1, "%s> %s", KMAG, KNRM);
	get_next_line(0, &line);
	while (ft_strcmp(limiter, line) != 0)
	{
		ft_printf_fd(1, "%s> %s", KMAG, KNRM);
		ft_putstr_nl_fd(line, pipo[1]);
		free(line);
		get_next_line(0, &line);
	}
	free(line);
	close_perror(pipo[1]);
	dup2_close(pipo[0], cmd->in);
	return (1);
}