/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_args.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:07:24 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 15:13:42 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(ptr, s1, len + 1);
	return (ptr);
}

t_args	*ft_args_init(t_cmd *cmd, char* str)
{
	t_args	*args;

	args = malloc(sizeof (t_args*));
	if (!args)
		ft_freestructs_exit(cmd, -1);
	args->next = NULL;
	if (!str)
		args->str = NULL;
	else
		args->str = ft_strdup(str);
	return (args);
}

t_args	*ft_args_last(t_args *args)
{
	if (!args)
		return (NULL);
	while (args->next)
		args = args->next;
	return (args);
}

void	ft_args_addback(t_args *start, t_args *new)
{
	t_args *tmp;

	if (!start)
		start = new;
	else
	{
		tmp = ft_args_last(start);
		tmp->next = new;
	}
}
