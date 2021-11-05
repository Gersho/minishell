//
// Created by Johan Chevet on 11/5/21.
//

#include "../../headers/minishell.h"

t_env	*env_dup(t_env *env)
{
	t_env	*cpy;

	cpy = NULL;
	while (env)
	{
		if (env->value)
			env_add_back(&cpy, new_env(ft_strdup(env->name), \
			ft_strdup(env->value)));
		else
			env_add_back(&cpy, new_env(ft_strdup(env->name), NULL));
		env = env->next;
	}
	return (cpy);
}
