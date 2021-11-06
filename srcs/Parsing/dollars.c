/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:42:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/06 15:25:25 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

int	ft_get_env_limit(char *str, int i)
{
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (i);
}

static void	ft_dollars_lastret(t_vars *vars, int *i)
{
	char		*tmp;
	char		*swap;
	t_quotes	limits;

	swap = ft_itoa(*vars->last_ret);
	if (!swap)
	{
		ft_freevars_exit(vars, -1);
	}
	limits.start = *i - 1;
	limits.end = *i + 1;
	ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - 2), *i);
	tmp = ft_build_newstr(vars, limits, swap);
	if (!tmp)
	{
		free(swap);
		ft_freevars_exit(vars, -1);
	}
	free(vars->str);
	vars->str = tmp;
	*i += ft_strlen(swap) - 1;
	free(swap);
}

static void	ft_dollars_to_env(t_vars *vars, int *i)
{
	char		*tmp;
	char		*swap;
	t_quotes	limits;

	limits.start = *i - 1;
	limits.end = ft_get_env_limit(vars->str, *i);
	tmp = ft_substr(vars->str, *i, limits.end - limits.start - 1);
	if (!tmp)
		ft_freevars_exit(vars, -1);
	swap = ft_get_env_value(vars, tmp);
	if (ft_get_type(vars->quotes, *i) == NONE && swap)
		swap = rm_redundant_spaces(vars, swap);
	ft_update_quote_data(vars, vars->quotes, \
		(ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
	*i += ft_strlen(swap) - ft_strlen(tmp) + 1;
	free(tmp);
	tmp = ft_build_newstr(vars, limits, swap);
	if (!tmp)
	{
		free(swap);
		ft_freevars_exit(vars, -1);
	}
	free(swap);
	free(vars->str);
	vars->str = tmp;
}

void	ft_handle_dollars(t_vars *vars)
{
	int			i;

	i = 0;
	while (vars->str[i])
	{
		if (vars->str[i] == (char) 36 && vars->str[i + 1]
			&& ft_get_type(vars->quotes, i) != SIMPLE)
		{
			i++;
			if (vars->str[i] == '?')
			{
				ft_dollars_lastret(vars, &i);
				continue ;
			}
			if (!ft_isalpha(vars->str[i]))
			{
				while (!is_separator(vars->str[i]) \
					&& vars->str[i] != 34 && vars->str[i] == 39)
					i++;
				continue ;
			}
			ft_dollars_to_env(vars, &i);
		}
		i++;
	}
}
