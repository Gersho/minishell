//
// Created by Stellar on 24/10/2021.
//

#include "../headers/minishell.h"

void 	exit_shell(char **param, t_env *env)
{
	//TODO free all
	free_env_list(env);
	exit(EXIT_SUCCESS);
}