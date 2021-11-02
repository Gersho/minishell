/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:05:05 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/02 13:52:59 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_init_vars(t_vars *vars, t_shell *shell, char *str)
{
	vars->cmd = shell->cmd;
	vars->str = str;
	vars->env_vars = shell->env;
	vars->last_ret = &shell->ret;
	vars->quotes = ft_quotes_init(vars, -1, -1, NONE);
	vars->env = ft_quotes_init(vars, -1, -1, NONE);
	if (!vars->quotes || !vars->env)
	{
		//todo free
	}
}

