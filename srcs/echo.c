//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

void echo(char **param)
{
	void (*put_str)(char *, int);
	int i;

	put_str = &ft_putstr_nl_fd;
	i = 1;
	if (param[i] && ft_strcmp("-n", param[i]) == 0)
	{
		put_str = &ft_putstr_fd;
		i++;
	}
	while (param[i])
	{
		put_str(param[i], 1);
		i++;
	}
	exit (EXIT_SUCCESS);
}