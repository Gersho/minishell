/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:07:45 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:27:25 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_check_after_pipe(t_vars *vars, int i, int len, t_cmd *tmp)
{
	if (!tmp->param[0] && !tmp->red[0])
	{
		ft_printf_fd(2, "%s: syntax error near unexpected token '|'\n",
			PROMPTERR);
		*vars->last_ret = 258;
		return (-255);
	}
	i += skip_spaces(&vars->str[i]);
	while (i < len)
	{
		if (vars->str[i] == '|')
		{
			ft_printf_fd(2, "%s: syntax error near unexpected token 'newline'\n",
				PROMPTERR);
			*vars->last_ret = 258;
			return (-255);
		}
		else
			return (1);
		i++;
	}
	ft_printf_fd(2, "%s: syntax error near unexpected token 'newline'\n",
		PROMPTERR);
	*vars->last_ret = 258;
	return (-255);
}

int	ft_handle_pipe(t_vars *vars, int i, int len, t_cmd **tmp)
{
	if (ft_check_after_pipe(vars, (i + 1), len, *tmp) == -255)
		return (-255);
	(*tmp)->next = ft_cmd_init();
	if (!(*tmp)->next)
		ft_freevars_exit(vars);
	*tmp = (*tmp)->next;
	return (0);
}
