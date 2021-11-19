/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:41:10 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:41:10 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*env_last(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = env_last(*lst);
		tmp->next = new;
	}
}
