/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_absolute_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:09 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:10 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_absolute_path(t_shell *shell, char **path_tab)
{
	if (**shell->cmd->param == '/' || **shell->cmd->param == '.')
	{
		ft_free_str_tab(path_tab);
		shell->cmd->path = ft_strdup(*shell->cmd->param);
		shell->ret = is_path_and_xok(shell->cmd->path);
		return (1);
	}
	return (0);
}
