/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/26 11:57:56 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
//#include <readline/history.h>
//TODO printf_fd
int main(int ac,char **av, char** env)
{
	char*	line;
	char	**env_t;
	t_cmd*	cmd;
	t_cmd*	tmp;
	char 	*prompt;
	//t_cmd*	tmp;

	(void)ac;
	(void)av;
	(void)env;

	t_cmd*	tmp;
	t_env	*env_l;

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
	
	env_l = get_env_list(env);
//	print_list(env_l);
//	printf("%s\n", set_prompt());
	//TODO segf if red alone ex: "echo >"
	while (1)
	{
		prompt = set_prompt(env_l);
		line = readline(prompt);
//		printf("in main :%s\n", env_l->name);
		cmd = ft_cmd_init();
		ft_parse_line(line, cmd);
//		dprintf(2, "line = |%s| cmd = |%s|\n", line, *cmd->param);
		if (*cmd->param)
			exec_cmd(cmd, &env_l);
		while (cmd != NULL)
		{
			tmp = cmd->next;
			free(cmd);
			cmd = NULL;
			cmd = tmp;
		}
		free(prompt);
		free(line);
		line = NULL;
	}
	return 0;
}