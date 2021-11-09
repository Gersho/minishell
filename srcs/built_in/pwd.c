/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:50 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:40:50 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pwd(char **param)
{
	char	buf[PATH_MAX];

	if (param[1] != NULL)
	{
		ft_printf_fd(2, "%s: pwd: too many arguments\n", PROMPTERR);
		return (EXIT_FAILURE);
	}
	else
		ft_printf_fd(1, "%s\n", getcwd(buf, PATH_MAX));
	return (EXIT_SUCCESS);
}
