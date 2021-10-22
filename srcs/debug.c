/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:06:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/22 15:33:46 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//DEBUG ONLY, REMOVE !!!!!!!
#include "../headers/minishell.h"

void ft_debug_quotes_env(t_vars *vars)
{
	t_quotes *tmp;
	tmp = vars->quotes;
	printf("quotes:\n");
	while (tmp)
	{
		printf("start:%d | end:%d | type:%d\n", tmp->start, tmp->end, tmp->type);
		tmp = tmp->next;
	}

	tmp = vars->env;
	printf("envs\n");
	while (tmp)
	{
		printf("start:%d | end:%d | type:%d\n", tmp->start, tmp->end, tmp->type);
		tmp = tmp->next;
	}
}