//
// Created by Stellar on 21/10/2021.
//

#include "../headers/minishell.h"

char	**init_env_tab(char **env)
{
	char	**env_t;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_t = ft_calloc(i, sizeof(char *));
	if (env_t == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_t[i] = ft_strdup(env[i]);
		if (env_t[i] == NULL)
		{
			ft_free_tab(env_t, i);
			return (NULL);
		}
		i++;
	}
	return (env_t);
}

char	*env_seeker(t_env *env_l, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (env_l && env_l->next)
	{
		if (strncmp(env_l->str, name, len) == 0)
			return (env_l->str + len);
		env_l = env_l->next;
	}
	return (NULL);
}
