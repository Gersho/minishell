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

	//TODO fix segfault with redirect without cmd->param
	env_l = get_env_list(env);
//	print_list(env_l);
	while (1)
	{
		prompt = set_prompt(env_l);
		line = readline(prompt);
		if (prompt)
			free(prompt);
//		printf("in main :%s\n", env_l->name);
		cmd = ft_cmd_init();
		ft_parse_line(line, cmd);
//		dprintf(2, "line = |%s| cmd = |%s|\n", line, *cmd->param);
		if (*cmd->param || cmd->red)
			exec_cmd(cmd, &env_l);
		free_cmd_list(cmd);
		free(line);
		line = NULL;
	}
	free_env_list(env_l);
	return 0;
}