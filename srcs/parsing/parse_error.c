/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:51:31 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/17 17:25:19 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	parse_error_quote(t_vars *vars)
{
	ft_printf_fd(2, "%s: syntax error unclosed quote\n", PROMPTERR);
	*vars->last_ret = 258;
	return (-255);
}
