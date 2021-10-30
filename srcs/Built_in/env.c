//
// Created by Johan Chevet on 10/22/21.
//

#include "../../headers/minishell.h"

int	env(t_env *env_l)
{
	print_list(env_l);
	return (EXIT_SUCCESS);
}
