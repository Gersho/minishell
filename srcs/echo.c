//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

void echo(char **param)
{
	int i;
	int nl;

	nl = 1;
	i = 1;
	if (param[i] && ft_strcmp("-n", param[i]) == 0)
	{
		nl = 0;
		i++;
	}
	while (param[i])
	{
		ft_putstr(param[i]);
		i++;
		if (param[i])
			ft_putchar(' ');
	}
	if (nl == 1)
		ft_putchar('\n');
	exit (EXIT_SUCCESS);
}