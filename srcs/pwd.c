//
// Created by Stellar on 21/10/2021.
//
//lol
#include "../headers/minishell.h"

void pwd(char **param, t_env *env_l)
{
	char buf[100];
	if (param[1] != NULL)
		ft_putstr_fd("pwd: too many arguments\n", 2);
	else
		printf("%s\n",getcwd(buf, 100));
//		printf("%s\n", env_seeker(env_l, "PWD="));
}