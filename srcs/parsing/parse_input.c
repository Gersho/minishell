/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/09 17:29:20 by kzennoun         ###   ########lyon.fr   */
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
	if (ret == -255)
		return (-255);
	else
		*i += ret;
	return (0);
}

static void	ft_parse_quotes(t_vars *vars, int len)
{
	int			i;
	t_quotes	tmp;

	i = 0;
	while (i < len)
	{
		if (ft_strncmp(&vars->str[i], "\'", 1) == 0)
		{
			tmp.start = i;
			tmp.end = ft_str_index_c((vars->str + i + 1), '\'') + i + 1;
			tmp.type = SIMPLE;
			ft_append_quote_data(vars, vars->quotes, tmp);
			i += tmp.end - tmp.start;
		}
		else if (ft_strncmp(&vars->str[i], "\"", 1) == 0)
		{
			tmp.start = i;
			tmp.end = ft_str_index_c((vars->str + i + 1), '\"') + i + 1;
			tmp.type = DOUBLE;
			ft_append_quote_data(vars, vars->quotes, tmp);
			i += tmp.end - tmp.start;
		}
		i++;
	}
}

static int	ft_check_after_pipe(t_vars *vars, int i, int len)
{
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

static int	ft_parse_loop(t_vars *vars, int len)
{
	t_cmd	*tmp;
	int		i;

	tmp = vars->cmd;
	i = 0;
	while (i < len)
	{
		i += skip_spaces(&vars->str[i]);
		if (ft_parse_checks(vars, &i, tmp) == -255)
			return (-255);
		if (ft_strncmp(&vars->str[i], "|", 1) == 0
			&& ft_get_type(vars->env, i) != ENVS)
		{
			if (ft_check_after_pipe(vars, (i + 1), len) == -255)
				return (-255);
			tmp->next = ft_cmd_init();
			if (!tmp->next)
				ft_freevars_exit(vars);
			tmp = tmp->next;
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

	ft_init_vars(&vars, shell, str);
	len = ft_strlen(vars.str);
	ft_parse_quotes(&vars, len);
	ft_handle_dollars(&vars, len);
	len = ft_strlen(vars.str);
	if (ft_parse_loop(&vars, len) == -255)
		return (-255);
	free(vars.str);
	free_quotes_list(vars.quotes);
	free_quotes_list(vars.env);
	return (0);
}
