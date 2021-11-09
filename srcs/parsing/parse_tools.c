/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/09 12:56:53 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	ft_param_loop(t_vars *vars, int *i)
{
	int	len;

	len = ft_strlen(vars->str);
	//while (vars->str[*i])
	while (*i < len)
	{
		if (vars->str[*i] == ' ')
			break ;
		if (is_separator(vars->str[*i]) && ft_get_type(vars->env, *i) != ENVS)
		{
			break ;
		}
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0)
		{
			*i += ft_str_index_c((&vars->str[*i] + 1), '\'') + 1;
		}
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0)
		{
			*i += ft_str_index_c((&vars->str[*i] + 1), '\"') + 1;
		}
		*i += 1;
	}
}

int	to_param_quote(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = ft_str_index_c((vars->str + i + 1), '\'') + i + 2;
	if (j == 0)
	{
		ft_printf_fd(2, "%s: syntax error unclosed quote\n", PROMPTERR);
		*vars->last_ret = 123;
		return (-255);
	}
	ft_param_loop(vars, &j);
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);
	if (!tmp)
		ft_freevars_exit(vars, -1);
	current->param = ft_param_append_word(vars, current->param, tmp);
	if (!current->param)
		ft_freevars_exit(vars, -1);
	free(tmp);
	return (j - i - 1);
}

int	to_param_dblquote(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = ft_str_index_c((vars->str + i + 1), '\"') + i + 2;
	if (j == 0)
	{
		ft_printf_fd(2, "%s: syntax error unclosed quote\n", PROMPTERR);
		*vars->last_ret = 123;
		return (-255);
	}
	ft_param_loop(vars, &j);
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);
	if (!tmp)
		ft_freevars_exit(vars, -1);
	current->param = ft_param_append_word(vars, current->param, tmp);
	if (!current->param)
		ft_freevars_exit(vars, -1);
	free(tmp);
	return (j - i - 1);
}

int	to_param_word(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = i + 1;
	ft_param_loop(vars, &j);
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);
	if (!tmp)
		ft_freevars_exit(vars, -1);
	current->param = ft_param_append_word(vars, current->param, tmp);
	if (!current->param)
		ft_freevars_exit(vars, -1);
	free(tmp);
	return (j - i);
}
