/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:42:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/24 00:23:53 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_get_env_limit(char *str, int i)
{
	int	len;

	len = ft_strlen(str);
	while (i < len)
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
		ft_freevars_exit(vars);
	}
	limits.start = *i - 1;
	limits.end = *i + 1;
	ft_update_quote_data(vars->quotes, (ft_strlen(swap) - 2), *i);
	tmp = ft_build_newstr(vars, limits, swap);
	if (!tmp)
	{
		free(swap);
		ft_freevars_exit(vars);
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
		ft_freevars_exit(vars);
	swap = ft_get_env_value(vars, tmp);
	if (ft_get_type(vars->quotes, *i) == NONE && swap)
		swap = rm_redundant_spaces(swap);
	ft_update_quote_data(vars->quotes, \
		(ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
	*i += (int)(ft_strlen(swap) - 2);
	free(tmp);
	tmp = ft_build_newstr(vars, limits, swap);
	if (!tmp)
	{
		free(swap);
		ft_freevars_exit(vars);
	}
	free(swap);
	free(vars->str);
	vars->str = tmp;
}

void	ft_invalid_dollar(t_vars *vars, int *i)
{
	t_quotes	limits;
	char		*tmp;
	char		*swap;

	limits.start = *i - 1;
	limits.end = *i + 1;
	swap = ft_strdup("");
	if (!swap)
		ft_freevars_exit(vars);
	ft_update_quote_data(vars->quotes, -2, *i);
	*i -= 2;
	tmp = ft_build_newstr(vars, limits, swap);
	if (!tmp)
	{
		free(swap);
		ft_freevars_exit(vars);
	}
	free(swap);
	free(vars->str);
	vars->str = tmp;
}

void	ft_handle_dollars(t_vars *vars, int len)
{
	int			i;

	i = 0;
	while (i < len)
	{
		if (vars->str[i] == (char) 36 && vars->str[i + 1]
			&& ft_get_type(vars->quotes, i) != SIMPLE)
		{
			i++;
			if (vars->str[i] == '?' || !ft_isalpha(vars->str[i]))
			{
				if (vars->str[i] == '?')
					ft_dollars_lastret(vars, &i);
				else if (!ft_isalpha(vars->str[i]))
					ft_invalid_dollar(vars, &i);
				continue ;
			}
			ft_dollars_to_env(vars, &i);
			len = ft_strlen(vars->str);
		}
		i++;
	}
}
