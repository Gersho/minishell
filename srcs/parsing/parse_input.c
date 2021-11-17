/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/17 11:20:44 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_parse_checks(t_vars *vars, int *i, t_cmd *tmp)
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

static int	ft_check_after_pipe(t_vars *vars, int i, int len, t_cmd *tmp)
{
	if (!tmp->param[0])
	{
		ft_printf_fd(2, "%s: syntax error near unexpected token '|'\n",
			PROMPTERR);
		*vars->last_ret = 258;
		return (-255);
	}
	i += skip_spaces(&vars->str[i]);
	while (i < len)
	{
		if (vars->str[i] == '|')
		{
			ft_printf_fd(2, "%s: syntax error near unexpected token 'newline'\n",
				PROMPTERR);
			*vars->last_ret = 258;
			return (-255);
		}
		else
			return (1);
		i++;
	}
	ft_printf_fd(2, "%s: syntax error near unexpected token 'newline'\n",
		PROMPTERR);
	*vars->last_ret = 258;
	return (-255);
}

static int	ft_handle_pipe(t_vars *vars, int i, int len, t_cmd **tmp)
{
	if (ft_check_after_pipe(vars, (i + 1), len, *tmp) == -255)
		return (-255);
	(*tmp)->next = ft_cmd_init();
	if (!(*tmp)->next)
		ft_freevars_exit(vars);
	*tmp = (*tmp)->next;
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
		ret = ft_parse_checks(vars, &i, tmp);
		if (ret == -255)
			return (-255);
		else if (ret != 0)
			continue ;
		if (ft_strncmp(&vars->str[i], "|", 1) == 0
			&& ft_get_type(vars->env, i) != ENVS)
		{
			if (ft_handle_pipe(vars, i, len, &tmp) == -255)
				return (-255);
			i++;
		}
		else if (vars->str[i] != ' ')
			i += to_param_word(vars, tmp, i);
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
		free_cmd_list(shell->cmd);
		shell->cmd = NULL;
		return (-255);
	}
	free(vars.str);
	free_quotes_list(vars.quotes);
	free_quotes_list(vars.env);
	return (0);
}
