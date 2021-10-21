/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:55:15 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:53:52 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	fd_print(char c, va_list varlist, t_flags *flags, int fd)
{
	int	check;

	check = 0;
	flags->conv = c;
	if (c == 'd' || c == 'i')
		check = fd_print_int(varlist, flags, fd);
	else if (c == 's')
		check = fd_print_str(varlist, flags, fd);
	else if (c == 'c')
		check = fd_print_char(varlist, flags, fd);
	else if (c == 'u')
		check = fd_print_uint(varlist, flags, fd);
	else if (c == 'x' || c == 'X')
		check = fd_print_hex(varlist, flags, fd);
	else if (c == 'p')
		check = fd_print_p(varlist, flags, fd);
	else if (c == '%')
		check = fd_print_percent(flags, fd);
	return (check);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	t_flags	flags;
	va_list	var_list;

	if (!str)
		return (-1);
	va_start(var_list, str);
	flags.char_printed = 0;
	while (*str)
	{
		fd_init_struct(&flags);
		if (fd_is_valid(&str, &flags, var_list))
		{
			if (fd_print(*str++, var_list, &flags, fd) == -1)
				return (-1);
		}
		else if (*str == '%' && *(str + 1) == '\0')
			str++;
		else
			flags.char_printed += write(fd, str++, 1);
	}
	va_end(var_list);
	return (flags.char_printed);
}
