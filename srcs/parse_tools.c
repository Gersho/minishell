/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/15 13:04:54 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	to_param_quote(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = ft_str_index_c(str, '\'');
	if (i == -1)
	{
		//pas de closing quote
	}
	tmp = ft_substr(str, 0, i);
	//if dollar ??
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_param_dblquote(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = ft_str_index_c(str, '\"');
	if (i == -1)
	{
		//pas de closing quote
	}
	tmp = ft_substr(str, 0, i);
	//if dollar ??
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_param_word(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = ft_str_index_c(str, ' ');
	if (i == -1)
		i = ft_strlen(str);
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}