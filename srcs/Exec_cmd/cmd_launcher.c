//
// Created by Johan Chevet on 11/4/21.
//

#include "../../headers/minishell.h"

void	launch_all_commands(t_shell *shell, int *status)
{
	int	i;

	i = 0;
	while (shell->cmd)
	{
		dup2_close(shell->cmd->in, 0);
		dup2_close(shell->cmd->out, 1);
		if (i == 0 && !shell->cmd->next && is_built_in(*shell->cmd->param))
		{
			exec_built_in(shell, 0);
			*status = -1;
		}
		else
			exec_cmd_fork(shell);
		if (!shell->cmd->next)
		{
			dup2(shell->std_in, 0);
			dup2(shell->std_out, 1);
		}
		shell->cmd = shell->cmd->next;
		i++;
	}
}
