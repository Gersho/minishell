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
	printf("\n%s%s%s", KGRN, "bash$ ", KNRM);
}
// todo export ne remplace pas une valeure existante quand tu fais export a a a a
// todo "export a" la value n'est pas NULL
// todo export Z="ls -l" ; $Z --> segfault
// todo peut pas lancer minishell dans minishell
// todo ctrl + D --> segfault
// todo exit doit afficher un exit
// todo quand ya des pipe les built-in ce lancent dans des fork
// todo command echo -nnnn -n -n -nq lol ne fait pas la meme chose que dans le bash
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
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		prompt = set_prompt(env_l);
		line = readline(prompt);
		if (prompt)
			free(prompt);
		cmd = ft_cmd_init();
		ft_parse_line(line, cmd);
		line = NULL;
		if (*cmd->param || cmd->red)
			exec_cmd(cmd, &env_l);
	}
	return 0;
}