/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:37:55 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:37:55 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

void	fd_int_field(t_flags *flags, int *size, int *value, int fd)
{
	if (flags->precision == 0 && *value == 0)
		*size = 0;
	if (flags->zero == 1 && *value < 0)
		write(fd, "-", 1);
	if (flags->precision >= *size)
	{
		flags->width -= flags->precision;
		flags->precision -= *size;
		if (*value < 0)
		{
			flags->precision += 1;
			flags->width -= 1;
		}
	}
	else
	{
		flags->width -= *size;
		flags->precision = 0;
	}
}

static int	mallocnul(char **to_print, int value)
{
	*to_print = ft_itoa(value);
	if (*to_print == NULL)
		return (-1);
	return (1);
}

int	fd_print_int(va_list varlist, t_flags *flags, int fd)
{
	int		size;
	int		value;
	char	*to_print;
	int		neg;

	neg = 0;
	value = (int)va_arg(varlist, int);
	if (!mallocnul(&to_print, value))
		return (-1);
	if (value < 0)
		neg = 1;
	size = ft_strlen(to_print);
	fd_int_field(flags, &size, &value, fd);
	if (!flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	if (!flags->zero && value < 0)
		write(fd, "-", 1);
	flags->char_printed += fd_print_precision(flags, fd);
	if (size > 0)
		ft_putstr_fd(to_print + neg, fd);
	if (flags->minus)
		flags->char_printed += fd_print_field(flags, fd);
	free(to_print);
	flags->char_printed += size;
	return (1);
}
