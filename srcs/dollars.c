/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:42:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/27 16:40:03 by kzennoun         ###   ########lyon.fr   */
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
	{
		//printf("coucou\n");
	}

	//rajouter les protections
	partA = ft_substr(vars->str, 0, limits.start);
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
	tmp = ft_substr(vars->str, limits.start + 1, limits.end - limits.start - 1);
	if (!tmp)
	{
		//free
	}
	swap = getenv(tmp);
	ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
	*i = *i + ft_strlen(swap);
	free(tmp);
	tmp = ft_build_newstr(vars, limits, swap);
	free(vars->str);
	vars->str = tmp;
	//printf("------->new str:%s\n", vars->str);
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
	tmp = ft_substr(vars->str, limits.start + 1, limits.end - limits.start - 1);
	if (!tmp)
	{
		//free
	}
	swap = getenv(tmp);
	swap = rm_redundant_spaces(vars, swap);
	ft_update_quote_data(vars, vars->quotes, (ft_strlen(swap) - ft_strlen(tmp) - 1), *i);
	*i = *i + ft_strlen(swap);
	free(tmp);
	tmp = ft_build_newstr(vars, limits, swap);
	free(vars->str);
	vars->str = tmp;
	//printf("------->new str:%s\n", vars->str);

}

int		ft_get_env_limit(char *str, int i)
{
	i++;
	while(str[i])
	{
		if (is_separator(str[i]) || is_quote_or_dollar(str[i]))
		{
			break ;
		}
		i++;
	}
	return (i);
}

void	ft_handle_dollars(t_vars *vars)
{
	int	i;
	t_type	type;

	i = 0;
	while (vars->str[i])
	{
		if (vars->str[i] == (char) 36)
		{
			type = ft_get_type(vars->quotes, i);
			if (type == NONE)
			{
				ft_env_expand_none(vars, &i);
			}
			else if (type == DOUBLE)
			{
				ft_env_expand_double(vars, &i);
			}
		}
		i++;
	}
}