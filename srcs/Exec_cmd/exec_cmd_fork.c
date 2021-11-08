//
// Created by Johan Chevet on 11/4/21.
//

#include "../../headers/minishell.h"

static void	free_cmd_and_exit(t_shell *shell)
{
	free_cmd_list(shell->cmd);
	exit(shell->ret);
}

int	exec_cmd_fork(t_shell *shell)
{
	char	**env_t;
	char	**path_tab;

	sig_child_handler(shell);
	shell->cmd->pid = fork();
	if (shell->cmd->pid == 0)
	{
		replace_std(shell->cmd->in, shell->cmd->out);
		if (shell->cmd->next)
			close_unused_fd(shell);
		if (exec_built_in(shell, 1))
			exit(shell->ret);
		path_tab = split_env_path(shell->env);
		shell->ret = get_cmd_path(shell, path_tab);
		env_t = get_env_tab(shell->env);
		if (shell->ret > 0)
			free_cmd_and_exit(shell);
		execve(shell->cmd->path, shell->cmd->param, env_t);
		perror(*shell->cmd->param);
		exit(EXIT_FAILURE);
	}
	else if (shell->cmd->pid == -1)
		perror("fork");
	close_multiple_fd(2, shell->cmd->in, shell->cmd->out);
	return (-1);
}
