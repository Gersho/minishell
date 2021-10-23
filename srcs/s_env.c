//
// Created by Johan Chevet on 10/21/21.
//

#include "../headers/minishell.h"

t_env *new(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof (t_env));
	env->name = name;
	env->value = value;
	env->prev = NULL;
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
		new->prev = tmp;
	}
}

t_env *get_env_list(char **env_main)
{
	t_env	*env;
	size_t	len;
	int		i;

	i = -1;

	env = NULL;
	while (env_main[++i])
	{
		len = ft_strchr(env_main[i], '=') - env_main[i];
		env_add_back(&env, new(ft_substr(env_main[i], 0, len), ft_substr(env_main[i], len + 1, ft_strlen(env_main[i]))));
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
		free(env->name);
		env->name = NULL;
		free(env->value);
		env->value = NULL;
		free(env);
		env = NULL;
		env = tmp;
	}
}

void print_list(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

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