//
// Created by Stellar on 24/10/2021.
//

#include "../../headers/minishell.h"

//TODO exit with args in unsigned char
void 	exit_shell(t_cmd *cmd, t_env *env)
{
	//TODO free all
	free_env_list(env);
	exit(EXIT_SUCCESS);
}