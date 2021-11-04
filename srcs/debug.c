/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:06:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/04 10:25:32 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_debug_quotes_env(t_vars *vars)
{
	t_quotes	*tmp;

	tmp = vars->quotes;
	ft_printf("quotes:\n");
	while (tmp)
	{
		ft_printf("start:%d | end:%d | type:%d\n",
			tmp->start, tmp->end, tmp->type);
		tmp = tmp->next;
	}
	tmp = vars->env;
	ft_printf("envs\n");
	while (tmp)
	{
		ft_printf("start:%d | end:%d | type:%d\n",
			tmp->start, tmp->end, tmp->type);
		tmp = tmp->next;
	}
}

void	ft_debug_cmd(t_cmd *cmd)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	tmp = cmd;
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->red[i])
		{
			ft_printf("j: %d | i: %d\n", j, i);
			ft_printf("cmd red: *%s*\n", tmp->red[i]);
			i++;
		}
		i = 0;
		while (tmp->param[i])
		{
			ft_printf("j: %d | i: %d\n", j, i);
			ft_printf("cmd param: *%s*\n", tmp->param[i]);
			i++;
		}
		j++;
		tmp = tmp->next;
	}
}
