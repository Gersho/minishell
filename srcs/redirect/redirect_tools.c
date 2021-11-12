/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:37 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:37 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

static void	redirect_out(char *redirect, int *red_mode)
{
	if (*redirect == '>')
	{
		if (*(redirect + 1) == '>')
			*red_mode = RED_OUT_A;
		else
			*red_mode = RED_OUT_T;
	}
}

static void	redirect_in(char *redirect, int *red_mode)
{
	if (*redirect == '<')
	{
		if (*(redirect + 1) == '<')
			*red_mode = HERE_DOC;
		else
			*red_mode = RED_IN;
	}
}

int	which_redirect(char *red)
{
	int	redirect_mode;

	redirect_mode = -1;
	redirect_in(red, &redirect_mode);
	redirect_out(red, &redirect_mode);
	return (redirect_mode);
}
