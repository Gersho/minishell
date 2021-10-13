/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_args.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:07:24 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 15:13:42 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"


t_args	*ft_args_last(t_args *args)
{
	if (!args)
		return (NULL);
	while (args->next)
		args = args->next;
	return (args);
}

void	ft_args_addback(t_args *start, t_args *new)
{
	t_args *tmp;

	if (!start)
		start = new;
	else
	{
		tmp = ft_args_last(start);
		tmp->next = new;
	}
}
