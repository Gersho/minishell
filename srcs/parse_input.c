/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/14 15:07:14 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_parse_line(char *str, t_cmd *cmd)
{
	int	i;
	t_cmd*	tmp;

	
	i = 0;
	tmp = cmd;
	while (str[i]!= '\0')
	{
		if (str[i] == "'")
		{
			//tmp->param

			//add to params** until next '
		}

		if (str[i] == '"')
		{
			//tmp->paramint			add_arg(t_cmd *cmd, char *input)
			//add to params** until next " 
		}

		if (str[i] == '|')
		{
			tmp->next = ft_cmd_init();
			tmp = tmp->next;
		}


		if (ft_strchr("<>", str[i]))
		{
			//send to red with watever is after (tmp not cmd)
		}


		//printf("%c", str[i]);
		i++;
	}
//	(void)cmd;
}