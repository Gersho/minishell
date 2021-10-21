//
// Created by Stellar on 21/10/2021.
//

#include "../headers/minishell.h"

void cd(char **param, t_env *env_l)
{
	int i;

	i = 0;
	while (param[i])
		i++;
	if (param[1] == NULL)
		chdir(env_seeker(env_l, "HOME="));
	else if (i > 4)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (i == 3)
		dprintf(2, "cd: string not in pwd: %s\n", param[1]);
	else if (chdir(param[1]) == -1)
		perror("cd");
}