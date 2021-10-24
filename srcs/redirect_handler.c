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
	if (is_redirect(str[i]) || str[i] == '\0')
	{
		if (is_redirect(str[i]))
			dprintf(2, "syntax error near unexpected token '%c'\n", str[i]);
		else
			dprintf(2, "syntax error near unexpected token 'newline'\n");
		return (NULL);
	}
	while (str[i] && !is_redirect(str[i]) && str[i] != ' ')//TODO ' ' && tab ?
		i++;
	filename = ft_calloc(i + 1, sizeof(char));
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
//		dprintf(2, "yooo\n");
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
	*red += skip_spaces(*red);
	return (redirect_mode);
}

int	redirect_handler(char *red, t_cmd *cmd)
{
	int 	redirect_mode;
	char	*filename;
	
	while (*red)
	{
		redirect_mode = which_redirect(&red);
		filename = get_filename(red);
//		dprintf(2, "filename=|%s|\n", filename);
		if (filename == NULL)
			exit (EXIT_FAILURE);//TODO free etc set var at exitfailure not exit
		red += ft_strlen(filename);
		if (redirect_mode == HERE_DOC)
			here_doc(filename, cmd);
		else
			open_with_param(filename, redirect_mode);
	}
	return (1);
}
