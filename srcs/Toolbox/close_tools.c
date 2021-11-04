//
// Created by Johan Chevet on 11/4/21.
//

#include "../../headers/minishell.h"

void	close_all_fds(t_shell *shell)
{
	while (shell->cmd)
	{
		close_perror(shell->cmd->in);
		close_perror(shell->cmd->out);
		shell->cmd = shell->cmd->next;
	}
	dup2(shell->std_in, 0);
	dup2(shell->std_out, 1);
}

void	close_unused_fd(t_shell *shell)
{
	t_cmd	*ptr;

	ptr = shell->cmd->next;
	while (ptr)
	{
		close_perror(ptr->in);
		close_perror(ptr->out);
		ptr = ptr->next;
	}
	close_perror(shell->std_out);
	close_perror(shell->std_in);
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
