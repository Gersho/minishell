/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/16 13:45:43 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	*g_ptr;

void	init_shell(t_shell *shell, char **line, char **env)
{
	*line = NULL;
	shell->env = get_env_list(env);
	shell->cmd = NULL;
	shell->ret = 0;
	tcgetattr(0, &shell->term);
	g_ptr = &shell->ret;
}

/*
 * Check if stdin, stdout and stderr are connected to terminal
 * It's to prevent an execution of bash/minishell in a pipe
 */
static void	check_isatty(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_printf_fd(2, "%s: You can't do that !!\n", PROMPTERR);
		exit(EXIT_FAILURE);
	}
}

static int	readline_protection(char *line, char *prompt, t_shell *shell)
{
	int	ret;

	ret = 0;
	if (prompt)
		free(prompt);
	if (!line)
		exit_shell(shell, 0);
	if (!*line)
	{
		free(line);
		ret = -255;
	}
	add_history(line);
	return (ret);
}

//TODO crash echo OLPWD if its NULL / any env that is null
int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	char	*line;
	char	*prompt;

	check_isatty(ac, av);
	init_shell(&shell, &line, env);
	while (1)
	{
		sig_pap_handler();
		prompt = set_prompt(&shell);
		line = readline(prompt);
		if (readline_protection(line, prompt, &shell) == -255)
			continue ;
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
