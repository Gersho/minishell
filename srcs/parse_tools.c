/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/14 17:34:30 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	to_param_quote(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = ft_strchr(str, (int) "'") - str;
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_param_dblquote(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = ft_strchr(str, (int) '"') - str;
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}
