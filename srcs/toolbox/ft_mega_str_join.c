/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mega_str_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:06 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:43:06 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/minishell.h"

static int	free_old_or_error(char *tmp, char *mega_str)
{
	if (!mega_str)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

/*
 * It join as many strings as you want
 */
char	*ft_mega_str_join(int nb, ...)
{
	char	*mega_str;
	char 	*tmp;
	int		i;
	va_list	args;

	mega_str = NULL;
	if (nb >= 2)
	{
		i = 0;
		va_start(args, nb);
		mega_str = ft_strdup(va_arg(args, char *));
		if (!mega_str)
			return (NULL);
		while (++i < nb)
		{
			tmp = mega_str;
			mega_str = ft_strjoin(mega_str, va_arg(args, char *));
			if (!free_old_or_error(tmp, mega_str))
				break ;
		}
		va_end(args);
		return (mega_str);
	}
	ft_putstr_fd("Not enough arguments\n", 2);
	return (mega_str);
}
