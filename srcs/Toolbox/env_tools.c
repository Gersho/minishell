//
// Created by Stellar on 21/10/2021.
//

#include "../../headers/minishell.h"

static char	**cpy_env_to_tab(t_env *env_l, char **env_t)
{
	char	*save;
	int		i;

	i = 0;
	while (env_l)
	{
		env_t[i] = ft_strjoin(env_l->name, "=");
		save = env_t[i];
		env_t[i] = ft_strjoin(save, env_l->value);
		free(save);
		if (env_t[i] == NULL)
		{
			ft_free_tab(env_t, i);
			return (NULL);
		}
		env_l = env_l->next;
		i++;
	}
	return (env_t);
}

char	**get_env_tab(t_env *env_l)
{
	char	**env_t;
	int 	len;

	len = env_list_size(env_l);
	env_t = ft_calloc(len + 1, sizeof(char *));
	if (env_t == NULL)
		return (NULL);
	env_t = cpy_env_to_tab(env_l, env_t);
	free_env_list(env_l);
	return (env_t);
}

int 	env_seeker(t_env **env_l, const char *name)
{
	t_env	*save;

	if (env_l)
	{
		save = *env_l;
		while (*env_l)
		{
			if (ft_strcmp((*env_l)->name, name) == 0)
				return (1);
			*env_l = (*env_l)->next;
		}
		*env_l = save;
	}
	return (0);
}

void	env_ch_value(t_env *old, char *new)
{
	if (old->value)
		free(old->value);
	old->value = ft_strdup(new);
}

t_env	*get_env_list(char **env_main)
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
