/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/14 18:05:14 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/readline.h>
//#include <readline/history.h>

int main()
{
	char*	line;
	t_cmd*	cmd;

	cmd = ft_cmd_init();
		printf("%p\n", cmd);
	// while (1)
	// {
		line = readline("Enter a line: ");
		ft_parse_line(line, cmd);
	//	printf("plip\n");
		free(line);
//	}
	printf("Still alive\n");
	int i = 0;

	// while (cmd->param[i])
	// {
	// 	printf("%s", cmd->param[i]);
	// 	i++;
	// }
	printf("%p\n", cmd);
	printf("%p\n", cmd->param);
	printf("%s\n", *cmd->param);

//	system(line);

	return 0;
}