/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:41:31 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:41:32 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*env_dup(t_env *env)
{
	t_env	*cpy;

	cpy = NULL;
	while (env)
	{
		if (env->value)
			env_add_back(&cpy, new_env(ft_strdup(env->name), \
			ft_strdup(env->value)));
		else
			env_add_back(&cpy, new_env(ft_strdup(env->name), NULL));
		env = env->next;
	}
	return (cpy);
}
