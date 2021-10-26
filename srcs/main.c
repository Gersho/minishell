/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/26 11:33:49 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/readline.h>
//#include <readline/history.h>

int main(int ac,char **av, char** env)
{
	char*	line;
	t_cmd*	cmd;
	t_cmd*	tmp;

	(void)ac;
	(void)av;
	(void)env;

	cmd = ft_cmd_init();

	// while (1)
	// {
		line = readline("$");
		//exit(0);
		ft_parse_line(line, cmd);
		//exec
	//	free(line); // line est deja free a la fin de ft_parse_line
		//exec_cmd(cmd, env);
//	}
		//printf("coucou\n");
		int i;
		int j = 0;
		tmp = cmd;

		while (tmp)
		{
			// printf("maillon cmd: %d", j);
			// j++;
			i = 0;
			printf("#########\n");
			printf("reds: %s\n", tmp->red);
			while (tmp->param[i])
			{
				printf("----\n");	
				printf("j: %d | i: %d\n", j, i);
				//printf("%p\n", tmp->param);
				printf("cmd param: %s\n", tmp->param[i]);
				i++;
			}
			j++;
			tmp = tmp->next;
		}
//	}
	
	return 0;
}