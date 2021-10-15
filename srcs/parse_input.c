/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/15 12:43:32 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_parse_line(char *str, t_cmd *cmd)
{
	int	i;
	t_cmd*	tmp;
	int len;

	// printf("tested line: %s\n", str);
	// printf("len = %zu\n", ft_strlen(str));
	i = 0;
	len = ft_strlen(str);
	tmp = cmd;
	while (i < len)
	{

		if (ft_strncmp(&str[i], "\'", 1) == 0)
		{
			i += to_param_quote(cmd, tmp, &str[i + 1]) + 2;
			continue;	
		}
		if (ft_strncmp(&str[i], "\"", 1) == 0)
		{
			i += to_param_dblquote(cmd, tmp, &str[i + 1]) + 2;
			continue;
		}
		if (ft_strncmp(&str[i], "|", 1) == 0)
		{
			tmp->next = ft_cmd_init();
			tmp = tmp->next;
			i++;
			continue;
		}


		// if (ft_strchr("<>", str[i]))
		// {
		// 	//send to red with watever is after (tmp not cmd)
		// }


		//printf("%c", str[i]);
		i++;
	}
//	(void)cmd;
}