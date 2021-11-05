//
// Created by Johan Chevet on 11/5/21.
//

#include "../../headers/minishell.h"

t_env	*env_last(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = env_last(*lst);
		tmp->next = new;
	}
}
