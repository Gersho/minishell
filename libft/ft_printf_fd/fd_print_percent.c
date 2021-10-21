/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:52:53 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:52:56 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	fd_print_percent(t_flags *flags, int fd)
{
	flags->width -= 1;
	if (!flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	flags->char_printed += write(fd, "%", 1);
	if (flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	return (1);
}
