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
	size_t i;
	
	i = 0;
	if (is_redirect(str[i]) || str[i] == '\0')
	{
		if (is_redirect(str[i]))
			dprintf(2, "syntax error near unexpected token '%c'\n", str[i]);
		else
			dprintf(2, "syntax error near unexpected token 'newline'\n");
		cmd->error = 1;
		return (NULL);
	}
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"')
			i++;
		i--;
	}
	while (str[i] && !is_redirect(str[i]) && str[i] != ' ')//TODO ' ' && tab ?
		i++;
	filename = ft_calloc(i + 1, sizeof(char));
	if (filename == NULL)
		return (NULL);
	ft_strlcpy(filename, str, i + 1);
	return (filename);
}

static int open_with_param(t_cmd *cmd, char *filename, int redirect_mode)
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
		perror(filename);
		return (EXIT_FAILURE);
	}
	if (redirect_mode == RED_OUT_A || redirect_mode == RED_OUT_T)
		dup2_close(file_fd, cmd->out);
	else
		dup2_close(file_fd, cmd->in);
	return (1);
}

static void redirect_out(char **redirect, int *red_mode)
{
	if (*(*redirect) == '>')
	{
		if (*(*redirect + 1) == '>')
		{
			(*redirect)++;
			*red_mode = RED_OUT_A;
		}
		else
			*red_mode = RED_OUT_T;
	}
}

static void redirect_in(char **redirect, int *red_mode)
{
	if (*(*redirect)== '<')
	{
		if (*(*redirect + 1) == '<')
		{
			(*redirect)++;
			*red_mode = HERE_DOC;
		}
		else
			*red_mode = RED_IN;
	}
}

static int which_redirect(char **red)
{
	int	redirect_mode;
	
	*red += skip_spaces(*red);
	redirect_in(red, &redirect_mode);
	redirect_out(red, &redirect_mode);
	(*red)++;
	*red += skip_spaces(*red);
	return (redirect_mode);
}

void	redirect_handler(t_cmd *cmd)
{
	char	*red_str;
	int 	redirect_mode;
	char	*filename;
	int 	pipe_fd[2];
	int 	first_cmd = 1;

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
		if (cmd->red)
		{
			red_str = cmd->red;
			while (*red_str)
			{
				redirect_mode = which_redirect(&red_str);
				filename = get_filename(red_str, cmd);
				if (filename == NULL)
					return ;
				red_str += ft_strlen(filename);
				if (redirect_mode == HERE_DOC)
					here_doc(filename, cmd);
				else
					open_with_param(cmd, filename, redirect_mode);
			}
		}
		first_cmd = 0;
		cmd = cmd->next;
	}
}