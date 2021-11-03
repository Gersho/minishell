/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:06:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/03 17:20:25 by kzennoun         ###   ########lyon.fr   */
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

void ft_debug_cmd(t_cmd *cmd)
{
	int i;
	int j = 0;
	t_cmd *tmp;
	tmp = cmd;

	while (tmp)
	{
		i = 0;
		printf("#########\n");
		while (tmp->red[i])
		{
			printf("----\n");	
			printf("j: %d | i: %d\n", j, i);
			printf("cmd red: *%s*\n", tmp->red[i]);
			i++;
		}
		i = 0;
		while (tmp->param[i])
		{
			printf("----\n");	
			printf("j: %d | i: %d\n", j, i);
			printf("cmd param: *%s*\n", tmp->param[i]);
			i++;
		}
		j++;
		tmp = tmp->next;
	}
}