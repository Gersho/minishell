//
// Created by Johan Chevet on 11/8/21.
//

#include "../../headers/minishell.h"

/*
 * Dup2 and close "in" by 0 and "out" by 1
 */
void	replace_std(int in, int out)
{
	dup2_close(in, 0);
	dup2_close(out, 1);
}
