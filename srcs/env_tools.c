//
// Created by Stellar on 21/10/2021.
//

#include "../headers/minishell.h"

char	**get_env_tab(t_env *env_l)
{
	char	**env_t;
	t_env 	*env_save;
	int		i;
	int 	len;
	char	*save;

	env_save = env_l;
	len = env_list_size(env_l);
	env_t = ft_calloc(len + 1, sizeof(char *));
	if (env_t == NULL)
		return (NULL);
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
	free_env_list(env_save);
	return (env_t);
}
/*Renvoie la valeur de la variable env*/
t_env 	*env_seeker(t_env *env_l, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (env_l && env_l->next)
	{
		if (ft_strncmp(env_l->name, name, len) == 0)
			return (env_l);
		env_l = env_l->next;
	}
	return (NULL);
}

void	env_ch_value(t_env *old, char *new)
{
	if (old->value)
		free(old->value);
	old->value = ft_strdup(new);
}
