/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_print_c_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:37:46 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:37:46 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	fd_print_char(va_list varlist, t_flags *flags, int fd)
{
	char	c;

	flags->char_printed += 1;
	flags->zero = 0;
	flags->width -= 1;
	c = (char)va_arg(varlist, int);
	if (!flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	ft_putchar_fd(c, fd);
	if (flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	return (1);
}

int	fd_print_str(va_list varlist, t_flags *flags, int fd)
{
	char	*str;
	int		len;

	str = (char *)va_arg(varlist, char *);
	if (!str)
		len = 6;
	else
		len = ft_strlen(str);
	if (flags->precision == 0)
		len = 0;
	if (flags->precision < len && flags->precision > 0)
		len = flags->precision;
	flags->width -= len;
	if (!flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	if (!str)
		flags->char_printed += write(fd, "(null)", len);
	else
		flags->char_printed += write(fd, str, len);
	if (flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	return (1);
}
