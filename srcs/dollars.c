/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:42:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/03 17:55:06 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_build_newstr(t_vars *vars, t_quotes limits, char *tmp)
{
	char		*partA;
	char		*partB;
	char		*swap;
	char		*final;
	t_quotes	env;
	if (tmp == NULL)
		return (vars->str);
	partA = ft_substr(vars->str, 0, limits.start);
	if (!partA)
		return (NULL);
	env.start = ft_strlen(partA);
	env.end = ft_strlen(partA) + ft_strlen(tmp) - 1;
	env.type = ENVS;
	ft_append_quote_data(vars, vars->env, env);
	partB = ft_substr(vars->str, limits.end, ft_strlen(vars->str));
	if (tmp == NULL)
	{
		swap = ft_strjoin(partA, "");
	}
	else
	{
		swap = ft_strjoin(partA, tmp);
	}
	final = ft_strjoin(swap, partB);
	free(partA);
	free(partB);
	free(swap);
	return (final);
}

void	ft_env_expand_double(t_vars *vars, int *i)
{
	char		*tmp;
	char		*swap;
	t_quotes	limits;


	limits.start = *i;
	limits.end = ft_get_env_limit((vars->str), *i);
	limits.type = NONE;
	limits.next = NULL;
	 printf("env expend none, start:%d*|end:%d*\n", limits.start, limits.end);
	if (limits.end - limits.start - 1 == 0)
	{
		tmp = ft_substr(vars->str, limits.start + 1, limits.end - limits.start);
	}
	else
	{
		tmp = ft_substr(vars->str, limits.start + 1, limits.end - limits.start - 1);

	}
	if (!tmp)
	{
		//free
	}
	swap = getenv(tmp);
	if (swap && swap[0] != '\0')
	{
		ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
		*i = *i + ft_strlen(swap);
		free(tmp);
		tmp = ft_build_newstr(vars, limits, swap);
	}
	else
	{
		ft_update_quote_data(vars, vars->quotes, (ft_strlen(tmp) - 1), *i);
		*i += 1;
		free(tmp);
		//limits.end = limits.end + 1;
		tmp = ft_build_newstr(vars, limits, swap);

	}
	free(vars->str);
	vars->str = tmp;
}

void	ft_env_expand_none(t_vars *vars, int *i)
{
	char		*tmp;
	char		*swap;
	t_quotes	limits;


	limits.start = *i;
	limits.end = ft_get_env_limit((vars->str), *i);
	limits.type = NONE;
	limits.next = NULL;
	// if (limits.end == -1)
	// 	return ;
	// printf("env expend none, start:%d*|end:%d*\n", limits.start, limits.end);
	if (limits.end - limits.start - 1 == 0)
	{
		tmp = ft_substr(vars->str, limits.start + 1, limits.end - limits.start);
	}
	else
	{
		tmp = ft_substr(vars->str, limits.start + 1, limits.end - limits.start - 1);

	}
	// printf("arg1:%d*|arg2:%d*|tmp:%s*\n", limits.start + 1, limits.end - limits.start - 1, tmp);
	if (!tmp)
	{
		//free
	}
	swap = getenv(tmp);
	// printf("swap:%s*\n", swap);
	if (swap && swap[0] != '\0')
	{
		swap = rm_redundant_spaces(vars, swap);
		ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
		*i = *i + ft_strlen(swap);
		free(tmp);
		tmp = ft_build_newstr(vars, limits, swap);
	}
	else
	{
		ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
		*i += 1;
		free(tmp);
		limits.end = limits.end + 1;
		tmp = ft_build_newstr(vars, limits, swap);

	}
	free(vars->str);
	vars->str = tmp;
	//printf("------->new str:%s\n", vars->str);

}

int		ft_get_env_limit(char *str, int i)
{

	while(str[i])
	{
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	ft_handle_dollars(t_vars *vars)
{
	int	i;
	t_type	type;
	t_quotes limits;
	char	*tmp;
	char	*swap;

	i = 0;
	while (vars->str[i])
	{
		if (vars->str[i] == (char) 36 && vars->str[i + 1] && ft_get_type(vars->quotes, i) != SIMPLE)
		{
			i++;
			if (vars->str[i] == '?')
			{
				swap = ft_itoa(*vars->last_ret);
				if (!swap)
				{
					ft_freevars_exit(vars, -1);
				}
				limits.start = i - 1;
				limits.end = i + 1;
				ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - 2), i);
				tmp = ft_build_newstr(vars, limits, swap);
				if (!tmp)
				{
					free(swap);
					ft_freevars_exit(vars, -1);
				}
				free(vars->str);
				vars->str = tmp;
				i += ft_strlen(swap) - 1;
				free(swap);
				continue ;
			}
			if (!ft_isalpha(vars->str[i]))
			{
				while (!is_separator(vars->str[i]) && vars->str[i] != 34 && vars->str[i] == 39)
					i++;
				continue ;
			}
			limits.start = i - 1;
			limits.end = ft_get_env_limit(vars->str, i);
			tmp = ft_substr(vars->str, i, limits.end - limits.start - 1);
			if (!tmp)
				ft_freevars_exit(vars, -1);
			swap = ft_get_env_value(vars, tmp);
			if (ft_get_type(vars->quotes, i) == NONE)
				swap = rm_redundant_spaces(vars, swap);
			ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - ft_strlen(tmp) - 1), i);
			i += ft_strlen(swap) - ft_strlen(tmp) + 1;
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
		i++;
	}
}
