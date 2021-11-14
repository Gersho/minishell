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
		file_fd = open(filename, O_RDWR, S_IRWXU | S_IRWXG);
	if (file_fd == -1)
	{
		shell->error = 1;
		shell->ret = 1;
		print_error_prompt(filename);
		free(filename);
		return (EXIT_FAILURE);
	}
	if (redirect_mode == RED_OUT_A || redirect_mode == RED_OUT_T)
		dup2_close(file_fd, shell->cmd->out);
	else
		dup2_close(file_fd, shell->cmd->in);
	free(filename);
	return (1);
}

static void	read_through_redirect(t_shell *shell)
{
	int		redirect;
	char	*filename;
	int		i;

	i = -1;
	while (shell->cmd->red[++i])
	{
		if (which_redirect(shell->cmd->red[i]) == -1 || \
		which_redirect(shell->cmd->red[i]) == HERE_DOC)
			continue ;
		redirect = which_redirect(shell->cmd->red[i]);
		i++;
		filename = ft_strdup(shell->cmd->red[i]);
		if (filename == NULL)
		{
			perror("Malloc filename");
			return ;
		}
		open_with_param(shell, filename, redirect);
	}
	ft_free_str_tab(shell->cmd->red);
	shell->cmd->red = NULL;
	return ;
}

/*
 * If there is no heredoc, it will set cmd->in with the right input
 */
static void	set_cmd_in(int first_cmd, t_shell *shell, int pipe_in)
{
	if (shell->cmd->in == 0)
	{
		if (first_cmd)
			shell->cmd->in = dup(0);
		else
			shell->cmd->in = pipe_in;
	}
}

void	redirect_handler(t_shell *shell)
{
	int		pipe_fd[2];
	int		first_cmd;
	t_cmd	*start;

	first_cmd = 1;
	start = shell->cmd;
	while (shell->cmd)
	{
		set_cmd_in(first_cmd, shell, pipe_fd[0]);
		pipe(pipe_fd);
		if (shell->cmd->next)
			shell->cmd->out = pipe_fd[1];
		else
		{
			close_multiple_fd(2, pipe_fd[0], pipe_fd[1]);
			shell->cmd->out = dup(1);
		}
		read_through_redirect(shell);
		shell->cmd = shell->cmd->next;
		first_cmd = 0;
	}
	shell->cmd = start;
}
