/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:19:17 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/21 15:52:05 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_str_index_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	is_separator(char c)
{
	if (c == 60 || c == 62 || c == 32 || c == 124)
		return (1);
	return (0);
}

int	is_redirect_or_space(char c)
{
	if (c == 60 || c == 62 || c == 32)
		return (1);
	return (0);
}

int	is_quote_or_dollar(char c)
{
	if (c == 34 || c == 39 || c == 36)
		return (1);
	return (0);
}
