/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:53 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:42:53 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_all_fds(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->in != 0)
			close_perror(cmd->in);
		if (cmd->out != 1)
			close_perror(cmd->out);
		cmd = cmd->next;
	}
}

void	close_unused_fd(t_shell *shell, int pipe_in)
{
	t_cmd	*ptr;

	ptr = shell->cmd->next;
	if (ptr)
		close_perror(pipe_in);
	while (ptr)
	{
		if (ptr->in != 0)
			close_perror(ptr->in);
		if (ptr->out != 1)
			close_perror(ptr->out);
		ptr = ptr->next;
	}
}

void	close_multiple_fd(int nb, ...)
{
	va_list	fd_list;
	int		fd;
	int		i;

	i = 0;
	va_start(fd_list, nb);
	while (i < nb)
	{
		fd = (int) va_arg(fd_list, int);
		close_perror(fd);
		i++;
	}
	va_end(fd_list);
}

void	close_perror(int fd)
{
	if (close(fd) == -1)
		perror("close");
}

void	dup2_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		perror("dup2");
	close_perror(fd1);
}
