/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/04 13:13:35 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_param_loop(t_vars *vars, int *i)
{
	while (vars->str[*i])
	{
		if (is_separator(vars->str[*i]))
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

int	ft_red_loop(t_vars *vars, int *i)
{
	if (is_separator(vars->str[*i]))
	{
		ft_printf_fd(2, "%s: syntax error near unexpected token '%c'\n",
			PROMPTERR, vars->str[*i]);
		*vars->last_ret = 258;
		return (-255);
	}
	else if (vars->str[*i] == '\0')
	{
		ft_printf_fd(2, "%s: syntax error near unexpected token 'newline'\n",
			PROMPTERR);
		*vars->last_ret = 258;
		return (-255);
	}
	while (vars->str[*i])
	{
		if (is_separator(vars->str[*i]))
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
	return (0);
}

int	to_redirect(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = i + 1;
	if (vars->str[j] == vars->str[j - 1])
		j++;
	tmp = ft_substr(vars->str, i, j - i);
	if (!tmp)
		ft_freevars_exit(vars, -1);
	current->red = ft_param_append_word(vars, current->red, tmp);
	if (!current->red)
		ft_freevars_exit(vars, -1);
	j += skip_spaces(&vars->str[j]);
	k = j;
	if (ft_red_loop(vars, &k) == -255)
	{
		return (-255);
	}
	tmp = ft_no_signifiant_quote_substr(vars, j, k - 1);
	if (!tmp)
		ft_freevars_exit(vars, -1);
	current->red = ft_param_append_word(vars, current->red, tmp);
	if (!current->red)
		ft_freevars_exit(vars, -1);
	free(tmp);
	return (k - i);
}
