/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:12:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/04 11:16:21 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_error_exit(int err)
{
	perror("Error");
	exit(err);
}

void	ft_freevars_exit(t_vars *vars, int err)
{
	ft_free_vars(vars);
	ft_error_exit(-1);
}
