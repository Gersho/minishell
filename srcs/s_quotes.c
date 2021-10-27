/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:00:47 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/27 16:57:58 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_type	ft_get_type(t_quotes *quotes, int i)
{
	t_quotes	*tmp;
	
	tmp = quotes;
	while (tmp)
	{
		if (i > tmp->start && i < tmp->end)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (NONE);

}

t_quotes *ft_quotes_init(t_vars *vars, int start, int end, t_type type)
{
	t_quotes	*quotes;

	quotes = malloc(sizeof(t_quotes));
	if (!quotes)
		return (NULL);
	//printf("bob init\n");
	quotes->next = NULL;
	quotes->start = start;
	quotes->end = end;
	quotes->type = type;
	return (quotes);
}

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
		swap->next = ft_quotes_init(vars, tmp.start, tmp.end, tmp.type);
		if (!swap->next)
		{
			//free exit toussa toussa

		}
	}
}

void	ft_parse_quotes(t_vars *vars)
{
	int			i;
	t_quotes	tmp;

	i = 0;
	// printf("len: %d\n", len);
	while (vars->str[i])
	{
		//  printf("i: %d | c: %c\n", i, str[i]);
		if (ft_strncmp(&vars->str[i], "\'", 1) == 0)
		{
			// printf("in simple if\n");
			// printf("str index c: %d\n", ft_str_index_c((str + i + 1), '\''));
			tmp.start = i;
			tmp.end = ft_str_index_c((vars->str + i + 1), '\'') + i + 1;
			tmp.type = SIMPLE;
			ft_append_quote_data(vars, vars->quotes, tmp);
			i += tmp.end - tmp.start;
		}
		else if (ft_strncmp(&vars->str[i], "\"", 1) == 0)
		{
			// printf("in double if\n");
			// printf("str index c: %d\n", ft_str_index_c((str + i) + 1, '\"'));
			tmp.start = i;
			tmp.end = ft_str_index_c((vars->str + i + 1), '\"') + i + 1;
			tmp.type = DOUBLE;
			ft_append_quote_data(vars, vars->quotes, tmp);
			i += tmp.end - tmp.start;
		}
		i++;
	}
}


void	ft_update_quote_data(t_vars *vars, t_quotes *quotes, int size, int i)
{
	t_quotes *tmp;
	
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

int	ft_get_quote_count(t_vars *vars, int start, int end)
{
	t_quotes	*tmp;
	int			count;

	count = 0;
	//tmp = vars->quotes;
	while (start <= end)
	{
		//printf("start:%d -- end:%d\n", start, end);
		tmp = vars->quotes;
		while(tmp)
		{
			if (start == tmp->start || start == tmp->end)
				count++;
			tmp = tmp->next;
		}
		start++;
	}
	return (count);
}

int	ft_is_quote_data(t_vars *vars, int i)
{
	t_quotes *tmp;

	tmp = vars->quotes;
	while(tmp)
	{
		if (i == tmp->start || i == tmp->end)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

