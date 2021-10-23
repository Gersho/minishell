//
// Created by Johan Chevet on 10/23/21.
//

#include "../headers/minishell.h"

void	unset(char **param, t_env *env_l)
{
	t_env *tmp;
	int		i;

	i = 0;
	if (param[1] == NULL)
		return (ft_putstr_fd("unset: not enough arguments\n", 2));
	while (param[++i])
	{
		tmp = env_seeker(env_l, param[i]);
		if (tmp == NULL)
			continue ;
		env_unlink(tmp);
	}
	
}