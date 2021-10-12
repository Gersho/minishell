/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:07:24 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 13:03:43 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"

t_cmd	*ft_cmd_init(t_list *list)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof (t_cmd*));
	if (!cmd)
		ft_freestructs_exit(list, -1);
	cmd->str = NULL;
	cmd->next = NULL;
	return (cmd);
}
