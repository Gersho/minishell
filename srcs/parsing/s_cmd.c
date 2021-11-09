/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:43:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/04 11:16:37 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_cmd	*ft_cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->param = ft_param_init(cmd);
	cmd->red = ft_param_init(cmd);
	if (!cmd->param || !cmd->red)
		return (NULL);
	cmd->next = NULL;
	cmd->path = NULL;
	cmd->in = 0;
	cmd->out = 1;
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
	t_cmd	*tmp;

	if (!start)
		start = new;
	else
	{
		tmp = ft_cmd_last(start);
		tmp->next = new;
	}
}

size_t	ft_size_list(t_cmd *cmd_list)
{
	size_t	i;

	i = 0;
	while (cmd_list)
	{
		i++;
		cmd_list = cmd_list->next;
	}
	return (i);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		if (cmd->param)
			ft_free_str_tab(cmd->param);
		if (cmd->red)
			ft_free_str_tab(cmd->red);
		if (cmd->path)
			free(cmd->path);
		tmp = cmd->next;
		free(cmd);
		cmd = NULL;
		cmd = tmp;
	}
}
