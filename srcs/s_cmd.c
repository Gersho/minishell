/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:43:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 15:17:21 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"

t_cmd	*ft_cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd*));
	if (!cmd)
		ft_error_exit(-1);
	cmd->param = NULL;
	cmd->red = NULL;
	cmd->next = NULL;
	return (cmd);
}


t_cmd	*ft_cmd_last(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	ft_cmd_addback(t_cmd *start, t_cmd *new)
{
	t_cmd *tmp;

	if (!start)
		start = new;
	else
	{
		tmp = ft_cmd_last(start);
		tmp->next = new;
	}
}

size_t ft_size_list(t_args *arg_list)
{
	size_t i;

	i = 0;
	while (arg_list)
	{
		i++;
		arg_list = arg_list->next;
	}
	return (i);
}
