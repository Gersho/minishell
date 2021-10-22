/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/22 16:01:07 by kzennoun         ###   ########lyon.fr   */
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
	int			len;
	t_vars		vars;

	vars.cmd = cmd;
	vars.str = str;
	len = ft_strlen(str);
	vars.quotes = ft_quotes_init(&vars, -1, -1, NONE);
	vars.env = ft_quotes_init(&vars, -1, -1, NONE);
	if (!vars.quotes)
	{
		//todo free
	}
	ft_parse_quotes(&vars, str, len, vars.quotes);


	//ft_debug_quotes_env(&vars);


	ft_handle_dollars(&vars);

	exit(-2);
	len = ft_strlen(str);
	ft_parse_loop(cmd, str, len);

}
