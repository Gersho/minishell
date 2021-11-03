/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/03 17:55:56 by kzennoun         ###   ########lyon.fr   */
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
//TODO start OLDPWD AT NULL | IF UNSET PWD and cd nana OLDPWD=NULL
//TODO EXPORT unset IN MAJ == ERROR
int main(int ac,char **av, char** env)
{
	t_shell shell;
	char*	line;
	char 	*prompt;
	struct sigaction sa;

	(void)ac;//error if != 1 ?
	(void)av;

	shell.ret = 0;
//	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &sig_handler;
	//TODO fix segfault with redirect without cmd->param
	//TODO fix  < cat && > cat
	//TODO fix segf ctrl+d
	shell.env = get_env_list(env);
	shell.std_in = dup(0);
	shell.std_out = dup(1);
	sigaction(SIGINT, &sa, NULL);
	shell.ret = 0;
	while (1)
	{
		prompt = set_prompt(&shell);
		line = readline(prompt);
		if (prompt)
			free(prompt);
		if (!line)
			exit_shell(&shell, 0);
		if (!*line)
		{
			free(line);
			continue ;
		}

		add_history(line);		
		shell.cmd = ft_cmd_init();
		if (!shell.cmd)
		{
			free_env_list(shell.env);
			ft_error_exit(-1);
		}
		if (ft_parse_line(line, &shell) == -255)
			continue ;

		//ft_debug_cmd(shell.cmd);

		line = NULL;
		if (*shell.cmd->param || *shell.cmd->red)
			exec_cmd(&shell);
	}
}
