/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_put_field_and_prec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:42:55 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:42:55 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	fd_print_field(t_flags *flags, int fd)
{
	int	char_printed;

	char_printed = 0;
	if (flags->zero == 1)
	{
		while (char_printed < flags->width)
		{
			write(fd, "0", 1);
			char_printed++;
		}
	}
	else
	{
		while (char_printed < flags->width)
		{
			write(fd, " ", 1);
			char_printed++;
		}
	}
	return (char_printed);
}

int	print_precision(t_flags *flags, int fd)
{
	int	i;

	i = 0;
	while (i < flags->precision)
	{
		write(fd, "0", 1);
		i++;
	}
	return (i);
}
