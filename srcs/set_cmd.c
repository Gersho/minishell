//
// Created by Johan Chevet on 10/26/21.
//

#include "../headers/minishell.h"

void set_cmd_std_fd(t_cmd *cmd, t_fds *fds)
{
	while (cmd)
	{
		cmd->fd = fds;
		cmd = cmd->next;
	}
}