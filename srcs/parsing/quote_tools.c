/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:36:09 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/14 14:41:48 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_append_quote_data(t_vars *vars, t_quotes *quotes, t_quotes tmp)
{
	t_quotes	*swap;

	swap = quotes;
	if (quotes->start == -1)
	{
		quotes->start = tmp.start;
		quotes->end = tmp.end;
		quotes->type = tmp.type;
	}
	else
	{
		while (swap->next)
			swap = swap->next;
		swap->next = ft_quotes_init(tmp.start, tmp.end, tmp.type);
		if (!swap->next)
		{
			ft_free_vars(vars);
			ft_error_exit(-1);
		}
	}
}

void	ft_update_quote_data(t_quotes *quotes, int size, int i)
{
	t_quotes	*tmp;

	tmp = quotes;
	while (tmp)
	{
		if (tmp->start >= i)
			tmp->start += size;
		if (tmp->end >= i)
			tmp->end += size;
		tmp = tmp->next;
	}
}

void	ft_parse_quotes(t_vars *vars, int len)
{
	int			i;
	t_quotes	tmp;

	i = 0;
	while (i < len)
	{
		if (ft_strncmp(&vars->str[i], "\'", 1) == 0)
		{
			tmp.start = i;
			tmp.end = ft_str_index_c((vars->str + i + 1), '\'') + i + 1;
			tmp.type = SIMPLE;
			ft_append_quote_data(vars, vars->quotes, tmp);
			i += tmp.end - tmp.start;
		}
		else if (ft_strncmp(&vars->str[i], "\"", 1) == 0)
		{
			tmp.start = i;
			tmp.end = ft_str_index_c((vars->str + i + 1), '\"') + i + 1;
			tmp.type = DOUBLE;
			ft_append_quote_data(vars, vars->quotes, tmp);
			i += tmp.end - tmp.start;
		}
		i++;
	}
}
