//
// Created by Stellar on 14/10/2021.
//

#include "../headers/minishell.h"

static int check_minus_n(char **param, int *nl)
{
	int	i;
	int j;

	i = 1;
	while (param[i] && param[i][0] == '-' && param[i][1] == 'n')
	{
		j = 1;
		while (param[i][j] == 'n')
			j++;
		if (param[i][j] == '\0')
		{
			*nl = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}

int echo(char **param)
{
	int i;
	int nl;
	
	nl = 1;
	i = check_minus_n(param, &nl);
	while (param[i])
	{
		ft_putstr_fd(param[i], 1);
		i++;
		if (param[i])
			ft_putchar_fd(' ', 1);
	}
	if (nl == 1)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}