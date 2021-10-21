/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:52:53 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:52:56 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include "libft.h"
# include <stdarg.h>

typedef struct s_flags
{
	int			zero;
	int			minus;
	int			dot;
	int			width;
	int			precision;
	char		conv;
	int 		char_printed;
}				t_flags;

int				ft_printf_fd(int fd, const char *s, ...);

void			fd_init_struct(t_flags *flags);

int				fd_is_flag(char c);
int				fd_is_conv(char c);
void			fd_flags_parsing(t_flags *flags, char *str, va_list list, int end);
int				fd_is_valid(const char **str, t_flags *flags, va_list varlist);

int				fd_get_precision(char *str_flags, t_flags *flags, va_list varlist);
int				fd_get_width(char *str_flag, t_flags *flags, va_list varlist);

int				fd_print(char c, va_list list, t_flags *flags, int fd);
int				fd_print_field(t_flags *flags, int fd);
int				fd_print_precision(t_flags *flags, int fd);
int				fd_print_str(va_list varlist, t_flags *flags, int fd);
int				fd_print_char(va_list varlist, t_flags *flags, int fd);
int				fd_print_int(va_list var_list, t_flags *flags, int fd);
int				fd_print_uint(va_list varlist, t_flags *flags, int fd);
int				fd_print_hex(va_list varlist, t_flags *flags, int fd);
int				fd_print_p(va_list varlist, t_flags *flags, int fd);
int				fd_print_percent(t_flags *flags, int fd);

#endif
