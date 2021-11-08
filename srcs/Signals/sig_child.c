//
// Created by Johan Chevet on 11/8/21.
//

#include "../../headers/minishell.h"

static void	sig_child(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3", 2);
}

/*
 * Reset term and handle SIGINT / SIGQUIT
 */
void	sig_child_handler(t_shell *shell)
{
	tcsetattr(0, TCSANOW, &shell->term);
	signal(SIGINT, &sig_child);
	signal(SIGQUIT, &sig_child);
}
