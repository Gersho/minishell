/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_vars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:05:05 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/17 13:46:01 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_init_vars(t_vars *vars, t_shell *shell, char *str)
{
	vars->cmd = shell->cmd;
	vars->str = str;
	vars->env_vars = shell->env;
	vars->last_ret = &shell->ret;
	vars->quotes = ft_quotes_init(-1, -1, NONE);
	vars->env = ft_quotes_init(-1, -1, NONE);
	if (!vars->quotes || !vars->env)
	{
		free_cmd_list(vars->cmd);
		free(vars->str);
		free_env_list(vars->env_vars);
		if (vars->quotes)
			free_quotes_list(vars->quotes);
		if (vars->env)
			free_quotes_list(vars->env);
	}
}

void	ft_free_vars_continue(t_vars *vars)
{
	if (vars->cmd)
		free_cmd_list(vars->cmd);
	if (vars->str)
		free(vars->str);
//	if (vars->env_vars)
//		free_env_list(vars->env_vars);
	if (vars->quotes)
		free_quotes_list(vars->quotes);
	if (vars->env)
		free_quotes_list(vars->env);
}

void	ft_free_vars(t_vars *vars)
{
	if (vars->cmd)
		free_cmd_list(vars->cmd);
	if (vars->str)
		free(vars->str);
	if (vars->env_vars)
		free_env_list(vars->env_vars);
	if (vars->quotes)
		free_quotes_list(vars->quotes);
	if (vars->env)
		free_quotes_list(vars->env);
}
