/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/21 11:18:32 by kzennoun         ###   ########lyon.fr   */
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
	char 	*prompt;

	(void)ac;
	(void)av;

	t_cmd*	tmp;
	t_env	*env_l;
	t_fds fds;

	//TODO fix segfault with redirect without cmd->param
	//TODO fix  < cat && > cat
	env_l = get_env_list(env);
	init_fd(&fds);//do this once in main
//	print_list(env_l);
	while (1)
	{
		prompt = set_prompt(env_l);
		line = readline(prompt);
		if (prompt)
			free(prompt);
		cmd = ft_cmd_init();
		ft_parse_line(line, cmd);
		set_cmd_std_fd(cmd, &fds);
//		printf("param: %s | red: %s\n", cmd->param[0], cmd->red);
//		dprintf(2, "line = |%s| cmd = |%s|\n", line, *cmd->param);
		if (*cmd->param || cmd->red)
			exec_cmd(cmd, &env_l);
//		while (cmd != NULL)
//		{
//			printf("cmd->param=%s\n", cmd->param[0]);
//			cmd = cmd->next;
//		}
		free_cmd_list(cmd);
		free(line);
		line = NULL;
	}
	free_env_list(env_l);
	return 0;
}