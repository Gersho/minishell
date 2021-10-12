/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:12:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 12:57:24 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"

void	ft_error_exit(int err)
{
	perror("Error");
	exit(err);
}

void	ft_freestructs_exit(t_list *list, int err)
{
	(void)list;
	//free stuff, starting from end and with sub chains
	
	ft_error_exit(err);
}