/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:26 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:40:26 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_list(t_env *env)
{
	while (env)
	{
		if (env->value)
			ft_printf_fd(1, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

int	env(t_env *env_l)
{
	print_list(env_l);
	return (EXIT_SUCCESS);
}
