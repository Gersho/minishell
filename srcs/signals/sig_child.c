/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:45 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:45 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	sig_child(int sig)
{
	(void)sig;
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
