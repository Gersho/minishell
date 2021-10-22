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

t_env	*env_unlink(t_env *env)
{
	t_env *start;

	start = env;
	if (env->prev)
	{
		env->prev->next = env->next;
		while (start->prev)
			start = start->prev;
	}
	else
		start = start->next;
	if (env->next)
		env->next->prev = env->prev;
	free(env->name);
	free(env->value);
	free(env);
	env = NULL;
	return (start);
}

void 	print_env_export(t_env *env)
{
	t_env 	*save;
	t_env 	*cpy;

	cpy = env_dup(env);
	save = cpy;
	while (cpy)
	{
		save = cpy;
		while (cpy)
		{
			if (ft_strcmp(save->name, cpy->name) > 0)
				save = cpy;
			cpy = cpy->next;
		}
		printf("%s=%s\n", save->name, save->value);
		cpy = env_unlink(save);
	}
}
//export +AR=NON
void	export(char **param, t_env *env)
{
	t_env *env_l;
	char *name;
	char *tmp;
	int	i;
	int j;


	j = 1;
	if (param[1] == NULL)
		return (print_env_export(env));
	if (ft_isdigit((int)param[1][i]))
	{
		ft_printf_fd(2, "export: not an identifier: %s\n", param[1]);
		return ;
	}
	while (param[j])
	{
		i = 0;
		while (param[j][i])
		{
			if (param[j][i] == '+' || param[j][i] == '=')
			{
				name = ft_substr(param[j], 0, i);
				if (param[j][i] == '+' && param[j][i + 1] == '=')
				{
					env_l = env_seeker(env, name);
					if (env_l == NULL)
						env_add_back(&env, new(name, ft_substr(param[j], i + 2, ft_strlen(param[j]))));
					else
					{
						tmp = env_l->value;
						env_l->value = ft_strjoin(env_l->value, param[j] + i + 2);
						free(tmp);
					}
					break;
				}
				else if (param[j][i] == '=')
				{
					env_l = env_seeker(env, name);
					if (env_l == NULL)
						env_add_back(&env, new(name, ft_substr(param[j], i + 1, ft_strlen(param[j]))));
					else
					{
						free(env_l->value);
						env_l->value = ft_substr(param[j], i + 1, ft_strlen(param[j]));
					}
					break;
				}
			}
			i++;
			if (param[j][i] == '\0')
				env_add_back(&env, new(ft_strdup(param[j]), ft_strdup("")));
		}
		j++;
	}
}