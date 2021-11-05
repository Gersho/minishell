/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:19:17 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/05 16:10:26 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_str_index_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
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

char	*rm_redundant_spaces(t_vars *vars, char *str)
{
	char	**split;
	char	*out;
	char	*tmp;
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
		ft_freevars_exit(vars, -1);
	}
	return (tmp);
}
