/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_red.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:07:22 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/11 17:07:48 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"

t_red	*ft_red_init(t_list *list)
{
	t_red	*red;

	red = malloc(sizeof (t_red*));
	if (!red)
		ft_freestructs_exit(list, -1);
	red->str = NULL;
	red->next = NULL;
	return (red);
}
