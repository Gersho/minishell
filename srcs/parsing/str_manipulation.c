/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:43:13 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/06 13:29:18 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_space_join(char **out, char **split, int *i)
{
	char	*tmp;

	tmp = ft_strjoin(*out, split[*i]);
	if (!tmp)
	{
		free(*out);
		ft_free_str_tab(split);
		return (0);
	}
	free(*out);
	*out = tmp;
	if (split[*i + 1])
	{
		tmp = ft_strjoin(*out, " ");
		if (!tmp)
		{
			free(*out);
			ft_free_str_tab(split);
			return (0);
		}
		free(*out);
		*out = tmp;
	}
	*i += 1;
	return (1);
}

char	*rm_redundant_spaces(char *str)
{
	char	**split;
	char	*out;
	int		i;

	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	out = malloc(sizeof(char));
	if (!out)
	{
		ft_free_str_tab(split);
		return (NULL);
	}
	*out = '\0';
	i = 0;
	while (split[i])
	{
		if (!ft_space_join(&out, split, &i))
			return (NULL);
	}
	free(str);
	return (out);
}

static int	ft_get_quote_count(t_vars *vars, int start, int end)
{
	t_quotes	*tmp;
	int			count;

	count = 0;
	while (start <= end)
	{
		tmp = vars->quotes;
		while (tmp)
		{
			if (start == tmp->start || start == tmp->end)
				count++;
			tmp = tmp->next;
		}
		start++;
	}
	return (count);
}

static int	ft_is_quote_data(t_vars *vars, int i)
{
	t_quotes	*tmp;

	tmp = vars->quotes;
	while (tmp)
	{
		if (i == tmp->start || i == tmp->end)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_no_signifiant_quote_substr(t_vars *vars, int start, int end)
{
	int		cut;
	char	*tmp;
	int		i;

	cut = ft_get_quote_count(vars, start, end);
	tmp = malloc(sizeof(char) * (end - start - cut + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		if (ft_is_quote_data(vars, start) == 1)
		{
			start++;
		}
		else
		{
			tmp[i] = vars->str[start];
			i++;
			start++;
		}
	}
	tmp[i] = '\0';
	return (tmp);
}
