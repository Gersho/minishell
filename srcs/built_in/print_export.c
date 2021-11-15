/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:43 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:40:43 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	print_env_export(t_env *env)
{
	t_env	*to_parse;
	t_env	*cpy;
	t_env	*save;

	cpy = env_dup(env);
	save = cpy;
	while (cpy)
	{
		to_parse = save;
		while (to_parse)
		{
			if (ft_strcmp(cpy->name, to_parse->name) > 0)
				save = to_parse;
			to_parse = to_parse->next;
		}
		if (save->value)
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", save->name, save->value);
		else
			ft_printf_fd(1, "declare -x %s\n", save->name);
		cpy = env_unlink(cpy, save->name);
		save = cpy;
	}
	return (0);
}
