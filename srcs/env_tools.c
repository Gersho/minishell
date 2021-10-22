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

	env_save = env_l;
	len = env_list_size(env_l);
	env_t = ft_calloc(len + 1, sizeof(char *));
	if (env_t == NULL)
		return (NULL);
	i = 0;
	while (env_l)
	{
		env_t[i] = ft_strdup(env_l->str);
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

char	*env_seeker(t_env *env_l, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (env_l && env_l->next)
	{
		if (ft_strncmp(env_l->str, name, len) == 0)
			return (env_l->str + len);
		env_l = env_l->next;
	}
	return (NULL);
}
