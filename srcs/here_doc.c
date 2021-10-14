//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

void here_doc(int fd, char* limiter)
{
	int		len;
	char*	line;

	len = ft_strlen(limiter);
	get_next_line(0, &line);
	while (ft_strncmp(limiter, line, len) != 0)
	{
		ft_putstr_nl_fd(line, fd);
		free(line);
		get_next_line(0, &line);
	}
	free(line);
	dup2_close(fd, 0);
}