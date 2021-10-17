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

static int open_with_param(char *filename, int redirect_mode)
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
		exit (EXIT_FAILURE);
	}
	if (redirect_mode == RED_OUT_A || redirect_mode == RED_OUT_T)
		dup2_close(file_fd, STDOUT_FILENO);
	else
		dup2_close(file_fd, STDIN_FILENO);
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
	*red += skip_spaces(*red);//if is redirect syntax error near *red
	return (redirect_mode);
}

int	redirect_handler(char *red, t_cmd *cmd)
{
	int		mode;
	int 	redirect_mode;
	char	*filename;
	
	while (*red)
	{
//		redirect_mode = 0;
//		red += skip_spaces(red);
//		if (*red == '>')
//		{
//			if (*(red + 1) == '>')
//			{
//				redirect_mode = RED_OUT_A;
//				red++;
//			}
//			else
//				redirect_mode = RED_OUT_T;
//		}
//		else if (*red == '<')
//		{
//			if (*(red + 1) == '<')
//			{
//				redirect_mode = HERE_DOC;
//				red++;
//			}
//			else
//				redirect_mode = RED_IN;
//		}
		redirect_mode = which_redirect(&red);
//		red++;
//		red += skip_spaces(red);
		dprintf(2, "%s\n", red);
		filename = get_filename(red);
		if (filename == NULL)
			return (-1);
		red += ft_strlen(filename);
		if (redirect_mode == HERE_DOC)
			here_doc(filename, cmd);
		else
			open_with_param(filename, redirect_mode); //TODO close fd if more redirect
		
	}
	return (1);
}
