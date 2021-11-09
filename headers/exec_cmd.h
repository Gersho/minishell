/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:27 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:43:27 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
#define EXEC_CMD_H

#include "minishell.h"

void	launch_all_commands(t_shell *shell, int *status);
int		exec_cmd_fork(t_shell *shell);
int		exec_built_in(t_shell *shell, int in_fork);
int		is_built_in(char *param);
int		get_cmd_path(t_shell *shell, char **path_tab);
int		parse_cmd(t_shell *shell);
char	**split_env_path(t_env *env);

#endif
