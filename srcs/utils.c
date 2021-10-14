//
// Created by Johan Chevet on 10/14/21.
//

#include "../headers/minishell.h"

int skip_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	close_perror(int fd)
{
	if (close(fd) == -1)
	{
		perror("close");
		//TODO free all and exit ???
	}
}

void dup2_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		perror("dup2");
	close_perror(fd1);
}