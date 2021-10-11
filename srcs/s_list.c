/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:43:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/11 17:08:23 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"

t_list	*ft_list_init(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list*));
	if (!list)
		ft_error_exit(-1);
	list->cmd = NULL;
	list->red = NULL;
	list->next = NULL;
	return (list);
}
