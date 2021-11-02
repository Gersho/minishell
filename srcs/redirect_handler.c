//
// Created by Johan Chevet on 10/14/21.
//

#include "../headers/minishell.h"


int is_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

static char *get_filename(char *str, t_cmd *cmd)
{
	char	*filename;

	filename = ft_strdup(str);
	if (filename == NULL)
		return (NULL);
	return (filename);
}

static int open_with_param(t_shell *shell, char *filename, int redirect_mode)
{
	int 	file_fd;

	if (redirect_mode == RED_OUT_T)
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	else if (redirect_mode == RED_OUT_A)
		file_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00644);
	else if (redirect_mode == RED_IN)
		file_fd = open(filename, O_RDWR, S_IRWXU | S_IRWXG);
	if (file_fd == -1)
	{
		shell->error = 1;
		perror(filename);
		return (EXIT_FAILURE);
	}
	if (redirect_mode == RED_OUT_A || redirect_mode == RED_OUT_T)
		dup2_close(file_fd, shell->cmd->out);
	else
		dup2_close(file_fd, shell->cmd->in);
	return (1);
}

static void redirect_out(char *redirect, int *red_mode)
{
	if (*redirect == '>')
	{
		if (*(redirect + 1) == '>')
			*red_mode = RED_OUT_A;
		else
			*red_mode = RED_OUT_T;
	}
}

static void redirect_in(char *redirect, int *red_mode)
{
	if (*redirect == '<')
	{
		if (*(redirect + 1) == '<')
			*red_mode = HERE_DOC;
		else
			*red_mode = RED_IN;
	}
}

static int which_redirect(char *red)
{
	int	redirect_mode;
	
	redirect_in(red, &redirect_mode);
	redirect_out(red, &redirect_mode);
	return (redirect_mode);
}

void	redirect_handler(t_shell *shell)
{
	int 	redirect_mode;
	char	*filename;
	int 	pipe_fd[2];
	int 	first_cmd = 1;
	t_cmd 	*cmd;
	int		i;
	
	cmd = shell->cmd;
	while (cmd)
	{
		if (first_cmd)
			cmd->in = dup(0);
		else
			cmd->in = pipe_fd[0];
		
		pipe(pipe_fd);
		if (cmd->next)
			cmd->out = pipe_fd[1];
		else
		{
			close_perror(pipe_fd[0]);
			close_perror(pipe_fd[1]);
			cmd->out = dup(1);
		}
		i = 0;
		while (cmd->red[i])
		{
			redirect_mode = which_redirect(cmd->red[i]);
			i++;
			filename = get_filename(cmd->red[i], cmd);
			if (filename == NULL)
			{
				shell->error = 1;
				return;
			}
			if (redirect_mode == HERE_DOC)
				here_doc(filename, cmd);
			else
				open_with_param(shell, filename, redirect_mode);
			i++;
		}
		ft_free_str_tab(cmd->red);
		cmd->red = NULL;
		first_cmd = 0;
		cmd = cmd->next;
	}
}