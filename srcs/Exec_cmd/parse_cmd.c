//
// Created by Johan Chevet on 10/12/21.
//

#include "../../headers/minishell.h"

int	parse_cmd(t_shell *shell)
{
	int		pid;
	int		status;
	t_cmd	*save;

	status = 0;
	shell->error = 0;
	save = shell->cmd;
	redirect_handler(shell);
	if (!shell->error)
		pid = launch_all_commands(shell, &status);
	else
	{
		close_all_fds(shell);
		shell->ret = EXIT_FAILURE;
	}
	if (status != -1 && !shell->error)
	{
		waitpid(pid, &status, 0);
		shell->ret = WEXITSTATUS(status);
		while (wait(NULL) != -1)
			;
	}
	free_cmd_list(save);
	return (1);
}
