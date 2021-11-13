/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:31:35 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/12 16:41:08 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**ft_param_init(void)
{
	char	**tmp;

	tmp = malloc(sizeof(char *));
	if (!tmp)
		return (NULL);
	tmp[0] = NULL;
	return (tmp);
}

static int	ft_copy_param(char **param, char **tmp, char *new)
{
	int	i;

	i = 0;
	while (param[i] != NULL)
	{
		tmp[i] = ft_strdup(param[i]);
		if (!tmp[i])
		{
			ft_free_str_tab(tmp);
			return (0);
		}
		i++;
	}
	tmp[i] = ft_strdup(new);
	if (!tmp[i])
	{
		ft_free_str_tab(tmp);
		return (0);
	}
	return (1);
}

char	**ft_param_append_word(char **param, char *new)
{
	int		i;
	char	**tmp;

	if (!new || new[0] == '\0')
		return (param);
	i = 0;
	while (param[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	if (!ft_copy_param(param, tmp, new))
		return (NULL);
	tmp[i + 1] = NULL;
	ft_free_str_tab(param);
//	free(new);
	return (tmp);
}
