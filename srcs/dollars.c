/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:42:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/18 13:42:53 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_handle_dollars(t_cmd *cmd, char *str, int len)
{
	(void) cmd;
	(void) str;
	(void) len;

	if (ft_str_index_c(str, '$') != -1)
		return ;
	
}