//
// Created by Stellar on 21/10/2021.
//
//lol
#include "../headers/minishell.h"

void pwd(char **param, t_env *env_l)
{
	char buf[PATH_MAX];

	if (param[1] != NULL)
		ft_putstr_fd("pwd: too many arguments\n", 2);
	else
		printf("%s\n", getcwd(buf, PATH_MAX));
}