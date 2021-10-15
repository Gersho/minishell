/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/15 12:51:29 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/readline.h>
//#include <readline/history.h>

int main()
{
	char*	line;
	t_cmd*	cmd;
	t_cmd*	tmp;

	cmd = ft_cmd_init();

	while (1)
	{
		line = readline("Enter a line: ");
		ft_parse_line(line, cmd);
		//ft_parse_line(av[1], cmd);
		free(line);

		int i;
		tmp = cmd;

		while (tmp)
		{
			i = 0;
			while (cmd->param[i])
			{
				printf("i: %d\n", i);
				printf("%p\n", cmd->param);
				printf("cmd param: %s\n", cmd->param[i]);
				printf("----");	
				i++;
			}

			tmp = tmp->next;
		}
	}
	
	return 0;
}