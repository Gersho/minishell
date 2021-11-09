/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:41:49 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:41:50 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	launch_all_commands(t_shell *shell, int *status)
{
	int	i;

	i = 0;
	while (shell->cmd)
	{
		if (i == 0 && !shell->cmd->next && is_built_in(*shell->cmd->param))
		{
			exec_built_in(shell, 0);
			*status = -1;
		}
		else
			exec_cmd_fork(shell);
		shell->cmd = shell->cmd->next;
		i++;
	}
}
