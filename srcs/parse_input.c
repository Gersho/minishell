/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/17 12:41:53 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_parse_loop(t_cmd *cmd, char *str, int len)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(&str[i], " ", 1) == 0)
			i += skip_spaces(&str[i]);
		else if (ft_strncmp(&str[i], "\'", 1) == 0)
			i += to_param_quote(cmd, tmp, &str[i]);
		else if (ft_strncmp(&str[i], "\"", 1) == 0)
			i += to_param_dblquote(cmd, tmp, &str[i]);
		else if (ft_strncmp(&str[i], "|", 1) == 0)
		{
			tmp->next = ft_cmd_init();
			tmp = tmp->next;
			i++;
		}
		else if (str[i] == 60 || str[i] == 62)
			i += to_redirect(cmd, tmp, &str[i]);
		else
			i += to_param_word(cmd, tmp, &str[i]);
	}
}

void	ft_parse_line(char *str, t_cmd *cmd)
{
	int		len;

	len = ft_strlen(str);
	ft_parse_loop(cmd, str, len);
}
