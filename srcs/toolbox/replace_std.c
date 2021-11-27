/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_std.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:02 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/27 11:40:24 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * Dup2 and close "in" by 0 and "out" by 1
 */
void	replace_std(int in, int out)
{
	if (in != 0)
		dup2_close(in, 0);
	if (out != 1)
		dup2_close(out, 1);
}
