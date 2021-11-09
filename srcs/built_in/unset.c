/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:55 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:40:56 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	unset(char **param, t_env **env_l)
{
	t_env	*tmp;
	int		i;

	i = 0;
	if (param[1] == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (EXIT_FAILURE);
	}
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
	return (EXIT_SUCCESS);
}
