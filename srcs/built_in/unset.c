/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:55 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/12 13:03:28 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_arg_quantity(char **param)
{
	if (param[1] == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	unset(char **param, t_env **env_l)
{
	t_env	*tmp;
	int		i;
	int		ret;

	i = 0;
	ret = check_arg_quantity(param);
	while (param[++i])
	{
		if (!ft_isalpha((int)param[i][0]) && param[i][0] != '_')
		{
			ft_printf_fd(2, "%s: unset: '%s': not a valid identifier\n", \
			PROMPTERR, param[i]);
			ret = EXIT_FAILURE;
			continue ;
		}
		tmp = *env_l;
		if (env_seeker(&tmp, param[i]))
		{
			*env_l = env_unlink(*env_l, tmp->name);
			if (*env_l == NULL)
				break ;
		}
	}
	return (ret);
}
