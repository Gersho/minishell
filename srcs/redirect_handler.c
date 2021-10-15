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
	while (str[i] && !is_redirect(str[i]))
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
	
	if (redirect_mode == RED_OUT_T)
		file_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	else if (redirect_mode == RED_OUT_A)
		file_fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00644);
	else if (redirect_mode == RED_IN)
		file_fd = open(filename, O_RDWR, S_IRWXU | S_IRWXG);
	else if (redirect_mode == HERE_DOC)
		file_fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (file_fd == -1)
	{
		perror(filename);
		exit (EXIT_FAILURE);
	}
	if (redirect_mode == HERE_DOC)
		file_fd = here_doc(file_fd, filename);
	if (mode == STDOUT_FILENO)
		dup2_close(file_fd, STDOUT_FILENO);
	else
		dup2_close(file_fd, 0);
	return (1);
}

int	redirect_handler(char *red)
{
	int		mode;
	int 	redirect_mode;
	char	*filename;
	
	mode = 0;
	redirect_mode = 0;
	while (*red)
	{
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
		open_with_param(filename, redirect_mode, mode); //close fd if more redirect
	}
	return (1);
}
