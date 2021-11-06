//
// Created by Johan Chevet on 11/4/21.
//

#ifndef TOOLS_H
#define TOOLS_H

#include "minishell.h"

void	close_perror(int fd);
void	dup2_close(int fd1, int fd2);
void	close_multiple_fd(int nb, ...);
void 	close_unused_fd(t_shell *shell);
void 	close_all_fds(t_shell *shell);

int		env_seeker(t_env **env_l, const char *name);
char	**get_env_tab(t_env *env_l);
void	env_ch_value(t_env *old, char *new);
t_env	*get_env_list(char **env_main);


#endif
