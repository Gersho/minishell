/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/19 15:01:06 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_parse_quote_and_ret(t_vars *vars, int *i, t_cmd *tmp)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(&vars->str[*i], "\'", 1) == 0
		&& ft_get_type(vars->env, *i) != ENVS)
		ret = to_param_quote(vars, tmp, *i) + 1;
	else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0
		&& ft_get_type(vars->env, *i) != ENVS)
		ret = to_param_dblquote(vars, tmp, *i) + 1;
	else if ((vars->str[*i] == 60 || vars->str[*i] == 62)
		&& ft_get_type(vars->env, *i) != ENVS)
		ret = to_redirect(vars, tmp, *i);
	*i += ret;
	if (ret == -254 || ret == -255)
		return (-255);
	return (ret);
}

static int	ft_parse_pipe_and_word(t_vars *vars, int *i, t_cmd **tmp, int len)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(&vars->str[*i], "|", 1) == 0
		&& ft_get_type(vars->env, *i) != ENVS)
	{
		if (ft_handle_pipe(vars, *i, len, tmp) == -255)
			return (-255);
		*i += 1;
	}
	else if (vars->str[*i] != ' ')
	{
		ret = to_param_word(vars, *tmp, *i);
		if (ret == -255)
			return (-255);
		*i += ret;
	}
	return (0);
}

static int	ft_parse_loop(t_vars *vars, int len)
{
	t_cmd	*tmp;
	int		i;
	int		ret;

	tmp = vars->cmd;
	i = 0;
	while (i < len)
	{
		i += skip_spaces(&vars->str[i]);
		ret = ft_parse_quote_and_ret(vars, &i, tmp);
		if (ret == -255)
			return (-255);
		else if (ret != 0)
			continue ;
		if (ft_parse_pipe_and_word(vars, &i, &tmp, len) == -255)
			return (-255);
	}
	return (0);
}

int	ft_parse_line(char *str, t_shell *shell)
{
	t_vars		vars;
	int			len;

	shell->cmd = ft_cmd_init();
	if (!shell->cmd)
	{
		free_env_list(shell->env);
		ft_error_exit(-1);
	}
	ft_init_vars(&vars, shell, str);
	len = ft_strlen(vars.str);
	ft_parse_quotes(&vars, len);
	ft_handle_dollars(&vars, len);
	len = ft_strlen(vars.str);
	if (ft_parse_loop(&vars, len) == -255)
	{
		ft_free_vars_continue(&vars);
		shell->cmd = NULL;
		return (-255);
	}
	free(vars.str);
	free_quotes_list(vars.quotes);
	free_quotes_list(vars.env);
	return (0);
}
