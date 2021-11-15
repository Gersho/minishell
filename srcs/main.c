/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/14 15:03:03 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int*	g_ptr;

void init_shell(t_shell *shell, char **line, char **env)
{
	*line = NULL;
	shell->env = get_env_list(env);
	shell->cmd = NULL;
	shell->ret = 0;
	tcgetattr(0, &shell->term);
}

//TODO crash echo OLPWD if its NULL / any env that is null
int main(int ac,char **av, char **env)
{
	t_shell shell;
	char*	line;
	char 	*prompt;

	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1))
	{
		ft_printf_fd(2, "%s: You can't do that !!\n", PROMPTERR);
		exit(EXIT_FAILURE);
	}
	init_shell(&shell, &line, env);
	g_ptr = &shell.ret;
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
		line = NULL;
		if (*shell.cmd->param || *shell.cmd->red)
			parse_cmd(&shell);
		else if (shell.cmd)
		{
			free_cmd_list(shell.cmd);
			shell.cmd = NULL;
		}
	}
}
