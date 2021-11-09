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

void init_shell(t_shell *shell, char **line, char **env)
{
	*line = NULL;
	shell->env = get_env_list(env);
	shell->cmd = NULL;
	shell->ret = 0;
	tcgetattr(0, &shell->term);
}

int main(int ac,char **av, char** env)
{
	t_shell shell;
	char*	line;
	char 	*prompt;

	(void)ac;
	(void)av;
	init_shell(&shell, &line, env);
	while (1)
	{
		sig_pap_handler();
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
			parse_cmd(&shell);
	}
}
