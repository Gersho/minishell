/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/15 14:00:04 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_parse_line(char *str, t_cmd *cmd)
{
	int	i;
	t_cmd*	tmp;
	int len;

	//printf("tested line: %s\n", str);
	// printf("len = %zu\n", ft_strlen(str));
	i = 0;
	len = ft_strlen(str);
	tmp = cmd;
	while (i < len)
	{
		//printf("i: %d -- str[i]: %c\n", i, str[i]);

		if (ft_strncmp(&str[i], " ", 1) == 0)
		{
			i += skip_spaces(&str[i]);
			continue;
		}

		if (ft_strncmp(&str[i], "\'", 1) == 0)
		{
			i += to_param_quote(cmd, tmp, &str[i + 1]) + 2;
			continue;	
		}
		else if (ft_strncmp(&str[i], "\"", 1) == 0)
		{
			i += to_param_dblquote(cmd, tmp, &str[i + 1]) + 2;
			continue;
		}
		else if (ft_strncmp(&str[i], "|", 1) == 0)
		{
			tmp->next = ft_cmd_init();
			tmp = tmp->next;
			i++;
			continue;
		}
		else
		{
			//printf("dans alnum\n");
			i += to_param_word(cmd, tmp, &str[i]) + 1;
			continue;	
		}
		//else //if (ft_isalnum(str[i]))



		// if (ft_strchr("<>", str[i]))
		// {
		// 	//send to red with watever is after (tmp not cmd)
		// }


		//printf("%c", str[i]);
		i++;
	}
//	(void)cmd;
}