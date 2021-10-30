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
	if (sig == SIGINT)
		printf("\n%s%s%s", KGRN, "bash$ ", KNRM);
}

// todo change prompt err everywhere
// todo export Z="ls -l" ; $Z --> segfault
// todo ctrl + D --> segfault
// todo exit doit afficher un exit
// todo oldpwd at start is NULL
int main(int ac,char **av, char** env)
{
	t_shell shell;
	char*	line;
//	t_cmd*	cmd;
	char 	*prompt;
	struct sigaction sa;

	(void)ac;//error if != 1 ?
	(void)av;

	shell.exit_status = 0;
//	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &sig_handler;
	//TODO fix segfault with redirect without cmd->param
	//TODO fix  < cat && > cat
	//TODO fix segf ctrl+d
	shell.env = get_env_list(env);
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		prompt = set_prompt(&shell);
		line = readline(prompt);
		shell.exit_status = 1;
		if (prompt)
			free(prompt);
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		shell.cmd = ft_cmd_init();
		ft_parse_line(line, shell.cmd);
		line = NULL;
		if (*shell.cmd->param || shell.cmd->red)
			exec_cmd(&shell);
	}
	return 0;
}