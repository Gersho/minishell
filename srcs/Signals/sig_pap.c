//
// Created by Johan Chevet on 11/8/21.
//

#include "../../headers/minishell.h"

static void	sig_pap(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
 * Remove ^C with termcaps and redisplay prompt
 * Ignore ^\ signal
 */
void	sig_pap_handler(void)
{
	struct termios	terminos;

	tcgetattr(0, &terminos);
	terminos.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &terminos);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_pap);
}
