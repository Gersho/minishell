/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:19 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/25 12:59:34 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

typedef enum e_cmd_name
{
	NOT_BUILT_IN_M,
	ECHO_M,
	CD_M,
	PWD_M,
	EXPORT_M,
	UNSET_M,
	ENV_M,
	EXIT_M
}t_cmd_name;

int		echo(char **param);
int		pwd(void);
int		cd(char **param, t_env *env_l);
int		env(t_env *env_l);
int		export(char **param, t_env **env);
int		print_env_export(t_env *env);
int		unset(char **param, t_env **env_l);
void	exit_shell(t_shell *shell, int in_fork);

#endif
