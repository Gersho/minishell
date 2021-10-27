/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:05:05 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/26 13:15:33 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_init_vars(t_vars *vars, t_cmd *cmd, char *str)
{
	vars->cmd = cmd;
	vars->str = str;
	vars->quotes = ft_quotes_init(vars, -1, -1, NONE);
	vars->env = ft_quotes_init(vars, -1, -1, NONE);
	if (!vars->quotes || !vars->env)
	{
		//todo free
	}
}

