/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:06 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/27 13:32:24 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * It skip spaces :)
 */
int	skip_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

/*
 * display prompt error and the last error set in erno
 */
void	print_error_prompt(char *str)
{
	ft_printf_fd(2, "%s: ", PROMPTERR);
	perror(str);
}

char	*str_in_lower_case(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		str[i] = ft_tolower((int)str[i]);
		i++;
	}
	return (str);
}

/*
 * Free everything, reset terminal setting and
 * close std_in and std_out if needed.
 * Display last error and exit 1 if specified.
 */
void	free_all(t_shell *shell, int display_err_and_exit, char *err_name)
{
	if (shell->std_in > 0)
		close_perror(shell->std_in);
	if (shell->std_out > 1)
		close_perror(shell->std_out);
	tcsetattr(0, TCSANOW, &shell->term);
	free_env_list(shell->env);
	free_cmd_list(shell->cmd);
	rl_clear_history();
	if (display_err_and_exit)
	{
		perror(err_name);
		ft_putstr_fd("Exit Failure\n", 2);
		exit(EXIT_FAILURE);
	}
}
