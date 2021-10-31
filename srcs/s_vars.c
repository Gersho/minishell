/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:05:05 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/31 02:13:55 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_init_vars(t_vars *vars, t_cmd *cmd, char *str, t_env *env)
{
	vars->cmd = cmd;
	vars->str = str;
	vars->env_vars = env;
	vars->quotes = ft_quotes_init(vars, -1, -1, NONE);
	vars->env = ft_quotes_init(vars, -1, -1, NONE);
	if (!vars->quotes || !vars->env)
	{
		//todo free
	}
}

