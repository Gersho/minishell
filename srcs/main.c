/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/02 17:12:10 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void sig_handler(int sig)
{
	if (sig == SIGINT)
		printf("\n%s%s%s", KGRN, "bash$ ", KNRM);
}

// todo change prompt err everywhere
// todo export Z="ls -l" ; $Z --> segfault
//TODO start OLDPWD AT NULL | IF UNSET PWD and cd nana OLDPWD=NULL
//TODO EXPORT unset IN MAJ == ERROR
int main(int ac,char **av, char** env)
{
	t_shell shell;
	char*	line;
//	t_cmd*	cmd;
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
			shell.ret = 0;
			free(line);
			continue ;
		}

		add_history(line);
		shell.cmd = ft_cmd_init();
		if (ft_parse_line(line, &shell) == -255)
			continue ;
		//ft_parse_line(line, &shell);

/*
		int i;
		int j = 0;
		t_cmd *tmp;
		tmp = shell.cmd;

		while (tmp)
		{
			// printf("maillon cmd: %d", j);
			// j++;
			i = 0;
			printf("#########\n");
			while (tmp->red[i])
			{
				printf("----\n");	
				printf("j: %d | i: %d\n", j, i);
				//printf("%p\n", tmp->red);
				printf("cmd red: *%s*\n", tmp->red[i]);
				i++;
			}
			i = 0;
			while (tmp->param[i])
			{
				printf("----\n");	
				printf("j: %d | i: %d\n", j, i);
				//printf("%p\n", tmp->param);
				printf("cmd param: *%s*\n", tmp->param[i]);
				i++;
			}
			j++;
			tmp = tmp->next;
		}
*/

		line = NULL;
//		printf("%s\n", shell.cmd->param[1]);
		if (*shell.cmd->param || *shell.cmd->red)
			exec_cmd(&shell);
	}
}

/*
int main(int ac,char **av, char** env)
{
	char*	line;
	t_cmd*	cmd;
	t_cmd*	tmp;

	(void)ac;
	(void)av;
	(void)env;

	cmd = ft_cmd_init();
	line = readline("$");
	ft_parse_line(line, cmd);
	printf("#### PARSING COMPLETE ####\n");
	int i;
	int j = 0;
	tmp = cmd;
	while (tmp)
	{
		i = 0;
		printf("#########\n");
		while (tmp->red[i])
		{
			printf("----\n");	
			printf("j:%d | i:%d\n", j, i);
			printf("cmd red:%s*\n", tmp->red[i]);
			i++;
		}
		printf("||||||||||||\n");
		i = 0;
		while (tmp->param[i])
		{
			printf("----\n");	
			printf("j:%d | i:%d\n", j, i);
			printf("cmd param:%s*\n", tmp->param[i]);
			i++;
		}
		j++;
		tmp = tmp->next;
	}
	return 0;
}
*/