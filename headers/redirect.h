//
// Created by Johan Chevet on 11/5/21.
//

#ifndef REDIRECT_H
#define REDIRECT_H

#include "minishell.h"

void	redirect_handler(t_shell *shell);
int		here_doc(char *limiter, t_cmd *cmd);
int		which_redirect(char *red);

#endif
