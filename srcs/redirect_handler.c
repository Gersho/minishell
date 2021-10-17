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

static char *get_filename(char *str)
{
	char	*filename;
	size_t i;
	
	i = 0;
	//TODO if str[i] is redirect  "syntax error near unexpected token"
	while (str[i] && !is_redirect(str[i]) && str[i] != ' ')//TODO ' ' && tab ?
		i++;
	filename = malloc(sizeof(char) * (i + 1));
	if (filename == NULL)
		return (NULL);
	ft_strlcpy(filename, str, i + 1);
	return (filename);
}

static int open_with_param(char *filename, int redirect_mode, int mode)
{
	int 	file_fd;
	
	file_fd = 0;
	if (redirect_mode == RED_OUT_T)
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	else if (redirect_mode == RED_OUT_A)
		file_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00644);
	else if (redirect_mode == RED_IN)
		file_fd = open(filename, O_RDWR, S_IRWXU | S_IRWXG);
	if (file_fd == -1)
	{
		perror(filename);
		exit (EXIT_FAILURE);
	}
	if (mode == STDOUT_FILENO)
		dup2_close(file_fd, STDOUT_FILENO);
	else if (redirect_mode == RED_IN)
		dup2_close(file_fd, 0);
	return (1);
}

int	redirect_handler(char *red, t_cmd *cmd)
{
	int		mode;
	int 	redirect_mode;
	char	*filename;
	
	while (*red)
	{
		mode = 0;
		redirect_mode = 0;
		red += skip_spaces(red);
//		ft_putstr_nl_fd(red, 2);
		if (*red == '>')
		{
			mode = STDOUT_FILENO;
			if (*(red + 1) == '>')
			{
				redirect_mode = RED_OUT_A;
				red++;
			}
			else
				redirect_mode = RED_OUT_T;
		}
		else if (*red == '<')
		{
			mode = STDIN_FILENO;
			if (*(red + 1) == '<')
			{
				redirect_mode = HERE_DOC;
				red++;
			}
			else
				redirect_mode = RED_IN;
		}
		red++;
		red += skip_spaces(red);
		filename = get_filename(red);
		if (filename == NULL)
			return (-1);
		red += ft_strlen(filename);
		if (redirect_mode == HERE_DOC)
			here_doc(filename, cmd);
		else
			open_with_param(filename, redirect_mode, mode); //TODO close fd if more redirect
		
	}
	return (1);
}
