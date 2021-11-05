//
// Created by Johan Chevet on 11/4/21.
//

#include "../../headers/minishell.h"

int	exec_cmd_fork(t_shell *shell, int *pid)
{
	char	**env_t;
	char	**path_tab;

	*pid = fork();
	if (*pid == 0)
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
	else if (*pid == -1)
		perror("fork");
	return (-1);
}