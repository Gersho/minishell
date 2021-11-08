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

//void init_shell(t_shell *shell, char **line, char **env)
//{
//	*line = NULL;
//	shell->env = get_env_list(env);
//	shell->cmd = NULL;
//	shell->ret = NULL;
//}

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int ac,char **av, char** env)
{
	t_shell shell;
	char*	line;
	char 	*prompt;

	(void)ac;//error if != 1 ?
	(void)av;


	shell.env = get_env_list(env);
	shell.cmd = NULL;
	tcgetattr(0, &shell.term);
	struct termios terminos;
	tcgetattr(0, &terminos);
	line = NULL;
	shell.ret = 0;
	while (1)
	{
//		terminos.c_lflag &= ~ECHOCTL;
//		tcsetattr(0, TCSANOW, &terminos);
//		signal(SIGQUIT, SIG_IGN);
//		signal(SIGINT, &sig_handler);
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
