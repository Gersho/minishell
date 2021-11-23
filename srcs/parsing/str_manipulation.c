/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:43:13 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/24 00:24:28 by kzennoun         ###   ########lyon.fr   */
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
	ft_free_str_tab(split);
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

char	*ft_build_newstr(t_vars *vars, t_quotes limits, char *tmp)
{
	char		*part_a;
	char		*part_b;
	char		*swap;
	char		*final;
	t_quotes	env;

	part_a = ft_substr(vars->str, 0, limits.start);
	if (!part_a)
		return (NULL);
	env.start = ft_strlen(part_a);
	env.end = ft_strlen(part_a) + ft_strlen(tmp) - 1;
	env.type = ENVS;
	ft_append_quote_data(vars, vars->env, env);
	part_b = ft_substr(vars->str, limits.end, ft_strlen(vars->str));
	if (tmp == NULL)
		swap = ft_strdup(part_a);
	else
		swap = ft_strjoin(part_a, tmp);
	final = ft_strjoin(swap, part_b);
	free(part_a);
	free(part_b);
	free(swap);
	return (final);
}
