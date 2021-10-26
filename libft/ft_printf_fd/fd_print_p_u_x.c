/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_print_p_u_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:38:20 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:38:20 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

void	fd_field_sum(t_flags *flags, int *size)
{
	if (flags->precision >= *size)
	{
		flags->width -= flags->precision;
		flags->precision -= *size;
	}
	else
	{
		flags->width -= *size;
		flags->precision = 0;
	}
}

int	fd_print_uint(va_list varlist, t_flags *flags, int fd)
{
	unsigned int	value;
	int				size;
	char			*to_print;

	value = (unsigned int)va_arg(varlist, unsigned int);
	to_print = ft_u_itoa(value);
	if (!to_print)
		return (-1);
	size = ft_strlen(to_print);
	if (flags->precision == 0 && value == 0)
		size = 0;
	fd_field_sum(flags, &size);
	if (!flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	flags->char_printed += fd_print_precision(flags, fd);
	if (size > 0)
		ft_putstr_fd(to_print, fd);
	if (flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	free(to_print);
	flags->char_printed += size;
	return (1);
}

int	fd_print_hex(va_list varlist, t_flags *flags, int fd)
{
	unsigned int	value;
	int				size;
	char			*to_print;

	value = (unsigned int)va_arg(varlist, unsigned int);
	if (flags->conv == 'x')
		to_print = ft_u_itoa_base(value, "0123456789abcdef");
	else
		to_print = ft_u_itoa_base(value, "0123456789ABCDEF");
	if (!to_print)
		return (-1);
	size = ft_strlen(to_print);
	if (value == 0 && flags->precision == 0)
		size = 0;
	fd_field_sum(flags, &size);
	if (!flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	flags->char_printed += fd_print_precision(flags, fd);
	if (size > 0)
		ft_putstr_fd(to_print, fd);
	if (flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	free(to_print);
	flags->char_printed += size;
	return (1);
}

int	fd_print_p(va_list varlist, t_flags *flags, int fd)
{
	unsigned long long int	value;
	int						size;
	char					*to_print;

	value = va_arg(varlist, unsigned long long int);
	to_print = ft_ullitoa_base(value, "0123456789abcdef");
	if (!to_print)
		return (-1);
	size = ft_strlen(to_print);
	flags->width -= 2;
	fd_field_sum(flags, &size);
	if (!flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	flags->char_printed += write(fd, "0x", 2);
	flags->char_printed += fd_print_precision(flags, fd);
	ft_putstr_fd(to_print, fd);
	if (flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	flags->char_printed += size;
	free(to_print);
	return (1);
}
