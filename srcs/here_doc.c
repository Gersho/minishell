//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

int here_doc(int fd, char* limiter)
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
	close (fd);
	fd = open(".here_doc", O_RDWR, 00644);
	if (fd == -1)
		exit (EXIT_FAILURE);
	return (fd);
}