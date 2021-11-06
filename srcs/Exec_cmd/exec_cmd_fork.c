//
// Created by Johan Chevet on 11/4/21.
//

#include "../../headers/minishell.h"

void sig_child(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3", 2);
}

void sigo(int sig)
{
	write(1, "\n", 1);
	ft_printf("uypp\n");
}

int	exec_cmd_fork(t_shell *shell)
{
	char	**env_t;
	char	**path_tab;

	tcsetattr(0, TCSANOW, &shell->term);
	signal(SIGINT, &sig_child);
	signal(SIGQUIT, &sig_child);
	shell->cmd->pid = fork();
	if (shell->cmd->pid == 0)
	{
		if (shell->cmd->next)
			close_unused_fd(shell);
		if (exec_built_in(shell, 1))
			exit(shell->ret);
		path_tab = split_env_path(shell->env);
		shell->ret = get_cmd_path(shell, path_tab);
		env_t = get_env_tab(shell->env);
		if (shell->ret > 0)
		{
			free_cmd_list(shell->cmd);
			exit(shell->ret);
		}
		execve(shell->cmd->path, shell->cmd->param, env_t);
		perror(*shell->cmd->param);
		exit(EXIT_FAILURE);
	}
	else if (shell->cmd->pid == -1)
		perror("fork");
	return (-1);
}
