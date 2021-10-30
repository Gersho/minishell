/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/28 01:38:17 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
//#include <readline/history.h>

void sig_handler(int sig)
{
//	if (sig == SIGINT)
//		printf("\n%s%s%s", KGRN, "bash$ ", KNRM);
//	else if (sig == SIGABRT)
		printf("yo\n");
}

// todo change prompt err everywhere
// todo export Z="ls -l" ; $Z --> segfault
// todo ctrl + D --> segfault
// todo exit doit afficher un exit
// todo oldpwd at start is NULL
int main(int ac,char **av, char** env)
{
	char*	line;
	t_cmd*	cmd;
	char 	*prompt;
	struct sigaction sa;

	(void)ac;//error if != 1 ?
	(void)av;
	t_env	*env_l;

//	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &sig_handler;
	//TODO fix segfault with redirect without cmd->param
	//TODO fix  < cat && > cat
	//TODO fix segf ctrl+d
	env_l = get_env_list(env);
//	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	while (1)
	{
		prompt = set_prompt(env_l);
		line = readline(prompt);
		if (prompt)
			free(prompt);
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		cmd = ft_cmd_init();
		ft_parse_line(line, cmd);
		line = NULL;
		if (*cmd->param || cmd->red)
			exec_cmd(cmd, &env_l);
	}
	return 0;
}