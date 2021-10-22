//
// Created by Johan Chevet on 10/22/21.
//

#include "../headers/minishell.h"

t_env *env_dup(t_env *env)
{
	t_env *cpy;

	cpy = NULL;
	while (env)
	{
		env_add_back(&cpy, new(ft_strdup(env->name), ft_strdup(env->value)));
		env = env->next;
	}
	return (cpy);
}

void 	print_env_export(t_env *env)
{
	char	*save;
	t_env 	*start;
	t_env 	*cpy;
	int len;
	int i;

	i = 0;
	start = env;
	len = env_list_size(env);
	cpy = env_dup(env);
//	print_list(cpy);
	while (i < len)
	{
		env = start;
		while (env)
		{
			if (ft_strcmp(save, env->name) > 0)
			{
				save = env->name;
			}
			env = env->next;
		}
		printf("Name=%s\n", save);
		env_unlink()
		i++;
	}
	start = env;
}

void	export(char **param, t_env *env)
{
	if (param[1] == NULL)
		print_env_export(env);
}