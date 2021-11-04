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

#endif
