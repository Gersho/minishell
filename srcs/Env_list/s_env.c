//
// Created by Johan Chevet on 10/21/21.
//

#include "../../headers/minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof (t_env));
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

int		env_list_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	free_env_list(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->name);
		env->name = NULL;
		if (env->value)
			free(env->value);
		env->value = NULL;
		free(env);
		env = NULL;
		env = tmp;
	}
}

void	print_list(t_env *env)
{
	while (env)
	{
		if (env->value)
			ft_printf_fd(1, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
