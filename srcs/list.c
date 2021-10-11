/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:43:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/11 17:00:13 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"

t_list	*ft_list_init(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list*));
	if (!list)
		ft_error_exit(-1);
	list->cmd = NULL;
	list->red = NULL;
	list->next = NULL;
	return (list);
}

t_cmd	*ft_cmd_init(t_list *list)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof (t_cmd*));
	if (!cmd)
		ft_freestructs_exit(list, -1);
	cmd->str = NULL;
	cmd->next = NULL;
	cmd->token = NONE;
	return (cmd);
}

t_red	*ft_red_init(t_list *list)
{
	t_red	*red;

	red = malloc(sizeof (t_red*));
	if (!red)
		ft_freestructs_exit(list, -1);
	red->str = NULL;
	red->next = NULL;
	return (red);
}
