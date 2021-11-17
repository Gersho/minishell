/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:13 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:43:13 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*set_prompt(t_shell *shell)
{
	char	*prompt;
	char	*curr_dir;
	char	buf[PATH_MAX];
	char	*status;

	prompt = NULL;
	if (shell->ret == 0)
		status = "🌸 ";
	else
		status = "❌ ";
	getcwd(buf, PATH_MAX);
	curr_dir = ft_strrchr(buf, (int) '/') + 1;
	prompt = ft_mega_str_join(10, status, \
		KBLU, curr_dir, \
		KMAG, " (", \
		KCYN, getenv("USER"), \
		KMAG, "): ", \
		KNRM);
	if (!prompt)
		prompt = ft_strdup("\x1B[34mminishell: \x1B[0m");
	return (prompt);
}
