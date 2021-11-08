//
// Created by Johan Chevet on 10/12/21.
//

#include "../../headers/minishell.h"

int last_pid(t_cmd *cmd)
{
	cmd = ft_cmd_last(cmd);
	return (cmd->pid);
}

void wait_all_process(t_cmd *cmd, t_shell *shell)
{
	int status;
	int	nl;

	nl = 0;
	waitpid(last_pid(cmd), &status, 0);
	if (WIFSIGNALED(status))
	{
		nl = 1;
		if (WTERMSIG(status) == 2)
			shell->ret = 130;
		if (WTERMSIG(status) == 3)
			shell->ret = 131;

	}
	else
		shell->ret = WEXITSTATUS(status);
	while (waitpid(cmd->pid, &status, 0) != -1)
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) != SIGPIPE)
			nl = 1;
		cmd = cmd->next;
	}
	if (nl == 1)
		write(1, "\n", 1);
}

int	parse_cmd(t_shell *shell)
{
	int		status;
	t_cmd	*cmd_ptr;

	status = 0;
	shell->error = 0;
	cmd_ptr = shell->cmd;
	redirect_handler(shell);
	if (!shell->error)
		launch_all_commands(shell, &status);
	else
	{
		close_all_fds(shell);
		shell->ret = EXIT_FAILURE;
	}
	if (status != -1 && !shell->error)
		wait_all_process(cmd_ptr, shell);

	free_cmd_list(cmd_ptr);
	return (1);
}
