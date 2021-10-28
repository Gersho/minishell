/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:12:59 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/27 13:09:49 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd->path)
		free(cmd->path);
	if (cmd->param)
		ft_free_str_tab(cmd->param);
	if (cmd->red)
		free(cmd->red);
	free(cmd);
}

void	ft_cmd_loop(t_cmd *cmd)
{
	t_cmd	*tmp;

	while(cmd)
	{
		tmp = cmd;
		while (tmp)
		{
			if (tmp->next != NULL)
				tmp = tmp->next;
			else
			{
				ft_free_cmd(tmp);
				break ;
			}
		}
	}
}

void	ft_error_exit(int err)
{
	perror("Error");
	exit(err);
}

void	ft_freestructs_exit(t_vars *vars, int err)
{
	//(void)cmd;
	//free stuff, starting from end and with sub chains
	// ft_cmd_loop(cmd);
	// ft_error_exit(err);
}