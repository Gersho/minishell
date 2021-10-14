/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:12:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 14:51:47 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_error_exit(int err)
{
	perror("Error");
	exit(err);
}

void	ft_freestructs_exit(t_cmd *cmd, int err)
{
	(void)cmd;
	//free stuff, starting from end and with sub chains
	
	ft_error_exit(err);
}