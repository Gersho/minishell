/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/28 14:25:30 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int main()
{
	char*	line;
	t_cmd*	cmd;
	t_cmd*	tmp;

	line = readline("$");
	//exit(0);
	cmd = ft_cmd_init();
	ft_parse_line(line, cmd);

	int i;
	int j = 0;
	tmp = cmd;

	while (tmp)
	{
		// printf("maillon cmd: %d", j);
		// j++;
		i = 0;
		printf("#########\n");
		printf("reds: %s*\n", tmp->red);
		while (tmp->param[i])
		{
			printf("----\n");	
			printf("j: %d | i: %d\n", j, i);
			//printf("%p\n", tmp->param);
			printf("cmd param: %s*\n", tmp->param[i]);
			i++;
		}
		j++;
		tmp = tmp->next;
	}
	exit(0);
}