/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:55 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/12 13:03:28 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	unset(char **param, t_env **env_l)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (param[++i])
	{
		tmp = *env_l;
		if (env_seeker(&tmp, param[i]))
		{
			*env_l = env_unlink(*env_l, tmp->name);
			if (*env_l == NULL)
				break ;
		}
	}
	return (0);
}
