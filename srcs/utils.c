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
//	dprintf(2, "closed %d\n", fd);
	if (close(fd) == -1)
	{
//		dprintf(2, "failed %d\n", fd);
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

char *str_in_lower_case(char *s)
{
	int		i;
	char	*str;
	
	i = 0;
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		str[i] = ft_tolower((int)str[i]);
		i++;
	}
	return (str);
}