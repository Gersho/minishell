//
// Created by Johan Chevet on 10/21/21.
//

#include "../headers/minishell.h"

t_env *new(char *str)
{
	t_env *env;

	env = malloc(sizeof (t_env));
	env->str = ft_strdup(str);
	env->next = NULL;
	return (env);
}

t_env	*env_last(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

void env_add_back(t_env **lst, t_env *new)
{
	t_env *tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = env_last(*lst);
		tmp->next = new;
	}
}

t_env *get_env_list(char **env_main)
{
	t_env	*env;
	int		i;
	
	i = -1;
	env = NULL;
	while (env_main[++i]) {
		env_add_back(&env, new(env_main[i]));
	}
	return (env);
}

int	env_list_size(t_env *env)
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

void free_env_list(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->str);
		env->str = NULL;
		free(env);
		env = NULL;
		env = tmp;
	}
}

void print_list(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->str);
		env = env->next;
	}
}
