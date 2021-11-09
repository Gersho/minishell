/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:47:40 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:47:45 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf_fd.h"

int	fd_is_conv(char c)
{
	return (c == 'd' || c == 'i' || c == 'c' || c == 's' || c == 'u' || \
	c == 'p' || c == 'x' || c == 'X' || c == '%');
}

int	fd_is_flag(char c)
{
	return (c == '-' || (c >= '0' && c <= '9') || c == '.' || c == '*');
}

void	fd_init_struct(t_flags *flags)
{
	flags->zero = 0;
	flags->dot = 0;
	flags->minus = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->conv = ' ';
}

int	fd_is_valid(const char **str, t_flags *flags, va_list varlist)
{
	char	*str_flags;
	int		i;

	if (**str == '%' && *(*str + 1) != '\0')
	{
		*str += 1;
		str_flags = (char *)*str;
		i = 0;
		while (fd_is_flag(*(str_flags + i)))
			i++;
		*str += i;
		if (!fd_is_conv(**str))
			return (0);
		fd_flags_parsing(flags, str_flags, varlist, i);
		return (1);
	}
	return (0);
}

void	fd_flags_parsing(t_flags *flags, char *str_f, va_list varlist, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (str_f[i] >= '1' && str_f[i] <= '9')
			i += fd_get_width(str_f + i, flags, varlist);
		else if (str_f[i] == '*')
			fd_get_width(str_f + i, flags, varlist);
		else if (str_f[i] == '.')
		{
			flags->dot = 1;
			flags->precision = 0;
			if (str_f[i + 1] == '*' || ft_isdigit(str_f[i + 1]))
				i += fd_get_precision(str_f + i + 1, flags, varlist);
		}
		else if (str_f[i] == '0')
			flags->zero = 1;
		else if (str_f[i] == '-')
			flags->minus = 1;
		i++;
	}
	if (flags->zero && (flags->minus || (flags->dot && flags->precision != -1)))
		flags->zero = 0;
}
