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

/*
 * It skip spaces :)
 */
int	skip_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

/*
 * display prompt error and the last error set in erno
 */
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
