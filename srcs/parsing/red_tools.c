/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:59:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/13 17:26:01 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_check_syntax(t_vars *vars, int *i)
{
	if (is_separator(vars->str[*i]) && ft_get_type(vars->env, *i) != ENVS)
	{
		ft_printf_fd(2, "%s: syntax error near unexpected token '%c'\n",
			PROMPTERR, vars->str[*i]);
		*vars->last_ret = 258;
		return (-255);
	}
	else if (vars->str[*i] == '\0' && ft_get_type(vars->env, (*i - 1)) != ENVS)
	{
		ft_printf_fd(2, "%s: syntax error near unexpected token 'newline'\n",
			PROMPTERR);
		*vars->last_ret = 258;
		return (-255);
	}
	return (1);
}

static int	ft_red_loop(t_vars *vars, int *i)
{
	int	len;

	len = ft_strlen(vars->str);
	if (ft_check_syntax(vars, i) == -255)
		return (-255);
	while (*i < len)
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
		ft_freevars_exit(vars);
	current->red = ft_param_append_word(current->red, tmp);
	if (!current->red)
		ft_freevars_exit(vars);
	j += skip_spaces(&vars->str[j]);
	k = j;
	if (ft_red_loop(vars, &k) == -255)
		return (-255);
	tmp = ft_no_signifiant_quote_substr(vars, j, k - 1);
	if (!tmp)
		ft_freevars_exit(vars);
	current->red = ft_param_append_word(current->red, tmp);
	if (!current->red)
		ft_freevars_exit(vars);
	return (k - i);
}
