/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 14:33:20 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_parse_line(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[i]!= '\0')
	{


		if (str[i] == '|')
		{
			
		}
		else if (str[i] == '"') //double quote
		{

		}



		//printf("%c", str[i]);
		i++;
	}
	(void)cmd;
}