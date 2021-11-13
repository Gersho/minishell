/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:15 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:15 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	add_slash_to_path(char **path_tab)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		if (!tmp)
		{
			ft_free_str_tab(path_tab);
			return (-1);
		}
		free(path_tab[i]);
		path_tab[i] = tmp;
		i++;
	}
	return (1);
}

char	**split_env_path(t_env *env)
{
	char	**paths_tab;

	paths_tab = NULL;
	if (env_seeker(&env, "PATH"))
	{
		if (env->value)
		{
			paths_tab = ft_split(env->value, ':');
			if (paths_tab == NULL)
				exit(EXIT_FAILURE);
			add_slash_to_path(paths_tab);
		}
	}
	return (paths_tab);
}
