//
// Created by Johan Chevet on 11/5/21.
//

#ifndef ENV_LIST_H
#define ENV_LIST_H

#include "minishell.h"

struct s_env_list
{
	char	*name;
	char	*value;
	t_env	*next;
};

t_env	*new_env(char *name, char *value);
t_env 	*env_unlink(t_env *env_l, char *name);
t_env	*env_last(t_env *env);
void	env_add_back(t_env **lst, t_env *new);
int		env_list_size(t_env *env);
void	free_env_list(t_env *env);
t_env	*env_dup(t_env *env);
void	print_list(t_env *env);

#endif
