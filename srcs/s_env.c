//
// Created by Johan Chevet on 10/21/21.
//

#include "../headers/minishell.h"

t_env *new_env(char *name, char *value)
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
		env_add_back(&env, new_env(ft_substr(env_main[i], 0, len), ft_substr(env_main[i], len + 1, ft_strlen(env_main[i]))));
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

void print_list(t_env *env, int out)
{
	while (env)
	{
		if (env->value)
			ft_printf_fd(out, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

t_env *env_dup(t_env *env)
{
	t_env *cpy;
	
	cpy = NULL;
	while (env)
	{
		if (env->value)
			env_add_back(&cpy, new_env(ft_strdup(env->name), ft_strdup(env->value)));
		else
			env_add_back(&cpy, new_env(ft_strdup(env->name), NULL));
		env = env->next;
	}
	return (cpy);
}

t_env 	*env_unlink(t_env *env_l, char *name)
{
	t_env *new;
	t_env *tmp;

	new = NULL;
	while (env_l)
	{
		if (ft_strcmp(env_l->name, name) != 0)
		{
			if (env_l->value)
				env_add_back(&new, new_env(ft_strdup(env_l->name), ft_strdup(env_l->value)));
			else
				env_add_back(&new, new_env(ft_strdup(env_l->name), NULL));
		}
		tmp = env_l->next;
		free(env_l->name);
		free(env_l->value);
		free(env_l);
		env_l = NULL;
		env_l = tmp;
	}
	return (new);
}