/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:19:17 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/09 14:12:11 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_str_index_c(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_separator(char c)
{
	if (c == 60 || c == 62 || c == 32 || c == 124)
		return (1);
	return (0);
}

int	is_redirect_or_space(char c)
{
	if (c == 60 || c == 62 || c == 32)
		return (1);
	return (0);
}

int	is_quote_or_dollar(char c)
{
	if (c == 34 || c == 39 || c == 36)
		return (1);
	return (0);
}

char	*ft_get_env_value(t_vars *vars, char *name)
{
	char	*tmp;
	t_env	**envs;

	envs = &vars->env_vars;
	if (env_seeker(envs, name) == 0)
		return (NULL);
	tmp = ft_strdup((*envs)->value);
	if (!tmp)
	{
		free(name);
		ft_freevars_exit(vars);
	}
	return (tmp);
}
