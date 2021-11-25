/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:50 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/25 12:43:28 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pwd(char **param)
{
	char	buf[PATH_MAX];

	ft_printf_fd(1, "%s\n", getcwd(buf, PATH_MAX));
	return (EXIT_SUCCESS);
}
