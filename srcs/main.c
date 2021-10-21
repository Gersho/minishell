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
#include <readline/readline.h>
//#include <readline/history.h>
//TODO printf_fd
int main(int ac,char **av, char** env)
{
	char*	line;
	char	**env_t;
	t_cmd*	cmd;
	//t_cmd*	tmp;

	(void)ac;
	(void)av;

	t_cmd*	tmp;
	t_env	*env;
	
	env = get_env_list(env);
	env_t = init_env_tab(env);
	print_list(env);
	while (1)
	{
		line = readline(PROMPT);
//		get_next_line(0, &line);
		cmd = ft_cmd_init();
		ft_parse_line(line, cmd);
//		dprintf(2, "line = |%s| cmd = |%s|\n", line, *cmd->param);
		if (*cmd->param)
			exec_cmd(cmd, env);
		while (cmd != NULL)
		{
			tmp = cmd->next;
			free(cmd);
			cmd = NULL;
			cmd = tmp;
		}
		free(line);
		line = NULL;
	}
	return 0;
}