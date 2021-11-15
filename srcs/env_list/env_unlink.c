/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:41:37 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:41:37 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * Redo the env list without the "name" link
 */
t_env	*env_unlink(t_env *env_l, char *name)
{
	t_env	*new;
	t_env	*tmp;

	new = NULL;
	while (env_l)
	{
		if (ft_strcmp(env_l->name, name) != 0)
		{
			if (env_l->value)
				env_add_back(&new, \
				new_env(ft_strdup(env_l->name), ft_strdup(env_l->value)));
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
