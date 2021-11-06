//
// Created by Johan Chevet on 11/4/21.
//

#ifndef BUILT_IN_H
#define BUILT_IN_H

typedef enum e_cmd_name
{
	NOT_BUILT_IN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}t_cmd_name;


#include "minishell.h"

int 	echo(char **param);
int 	pwd(char **param);
int 	cd(char **param, t_env *env_l);
int 	env(t_env *env_l);
int 	export(char **param, t_env **env);
int 	unset(char **param, t_env **env_l);
void 	exit_shell(t_shell *shell, int in_fork);

#endif