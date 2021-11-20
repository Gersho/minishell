/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:33 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:34 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	open_with_param(t_shell *shell, char *filename, int redirect_mode)
{
	int	file_fd;

	file_fd = -1;
	if (redirect_mode == RED_OUT_T)
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	else if (redirect_mode == RED_OUT_A)
		file_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00644);
	else if (redirect_mode == RED_IN)
		file_fd = open(filename, O_RDONLY, S_IRWXU | S_IRWXG);
	if (file_fd == -1)
	{
		shell->error = 1;
		shell->ret = 1;
		print_error_prompt(filename);
		return (EXIT_FAILURE);
	}
	if (redirect_mode == RED_OUT_A || redirect_mode == RED_OUT_T)
		dup2_close(file_fd, shell->cmd->out);
	else
		dup2_close(file_fd, shell->cmd->in);
	return (0);
}

void	redirect_handler(t_shell *shell)
{
	int		redirect;
	int		i;

	i = -1;
	while (shell->cmd->red[++i])
	{
		if (which_redirect(shell->cmd->red[i]) == -1 || \
		which_redirect(shell->cmd->red[i]) == HERE_DOC)
			continue ;
		redirect = which_redirect(shell->cmd->red[i]);
		i++;
		if (open_with_param(shell, shell->cmd->red[i], redirect) == 1)
			break ;
	}
	ft_free_str_tab(shell->cmd->red);
	shell->cmd->red = NULL;
}
