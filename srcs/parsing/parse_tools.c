/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/17 16:59:51 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_param_loop(t_vars *vars, int *i)
{
	int	len;
	int	ret;

	len = ft_strlen(vars->str);
	while (*i < len)
	{
		if (vars->str[*i] == ' ')
			break ;
		if (is_separator(vars->str[*i]) && ft_get_type(vars->env, *i) != ENVS)
			break ;
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0)
		{
			ret = ft_str_index_c((&vars->str[*i] + 1), '\'');
			*i += ret + 1;
		}
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0)
		{
			ret = ft_str_index_c((&vars->str[*i] + 1), '\"');
			*i += ret + 1;
		}
		if (ret == -1)
			return (-255);
		*i += 1;
	}
	return (0);
}

int	to_param_quote(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = ft_str_index_c((vars->str + i + 1), '\'');
	if (j == -1)
		return (parse_error_quote(vars));
	j += i + 2;
	if (ft_param_loop(vars, &j) == -255)
		return (parse_error_quote(vars));
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);
	if (!tmp)
		ft_freevars_exit(vars);
	current->param = ft_param_append_word(current->param, tmp);
	if (!current->param)
		ft_freevars_exit(vars);
	return (j - i - 1);
}

int	to_param_dblquote(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = ft_str_index_c((vars->str + i + 1), '\"');
	if (j == -1)
		return (parse_error_quote(vars));
	j += i + 2;
	if (ft_param_loop(vars, &j) == -255)
		return (parse_error_quote(vars));
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);
	if (!tmp)
		ft_freevars_exit(vars);
	current->param = ft_param_append_word(current->param, tmp);
	if (!current->param)
		ft_freevars_exit(vars);
	return (j - i - 1);
}

int	to_param_word(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = i + 1;
	if (ft_param_loop(vars, &j) == -255)
		return (parse_error_quote(vars));
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);
	if (!tmp)
		ft_freevars_exit(vars);
	current->param = ft_param_append_word(current->param, tmp);
	if (!current->param)
		ft_freevars_exit(vars);
	return (j - i);
}
