/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:06 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:43:06 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	skip_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	print_error_prompt(char *str)
{
	ft_printf_fd(2, "%s: ", PROMPTERR);
	perror(str);
}

char	*str_in_lower_case(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		str[i] = ft_tolower((int)str[i]);
		i++;
	}
	return (str);
}

char	*ft_mega_str_join(int nb, ...)
{
	char	*mega_str;
	char	*str;
	char	*tmp;
	int		i;
	va_list	args;

	i = 1;
	va_start(args, nb);
	mega_str = (char *) va_arg(args, char *);
	while (i < nb)
	{
		str = (char *) va_arg(args, char *);
		tmp = mega_str;
		mega_str = ft_strjoin(mega_str, str);
		if (!mega_str)
		{
			va_end(args);
			return (NULL);
		}
		if (i > 1)
			free(tmp);
		i++;
	}
	va_end(args);
	return (mega_str);
}
