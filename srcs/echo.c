//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

//TODO -nnnnnnnn works
void echo(char **param, int out)
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
		ft_putstr_fd(param[i], out);
		i++;
		if (param[i])
			ft_putchar_fd(' ', out);
	}
	if (nl == 1)
		ft_putchar_fd('\n', out);
}