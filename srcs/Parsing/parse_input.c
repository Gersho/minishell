/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/06 11:49:55 by kzennoun         ###   ########lyon.fr   */
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
}

int	ft_parse_loop(t_vars *vars)
{
	t_cmd	*tmp;
	int		i;

	tmp = vars->cmd;
	i = 0;
	while (vars->str[i])
	{
		if (ft_strncmp(&vars->str[i], " ", 1) == 0)
			i += skip_spaces(&vars->str[i]);
		else if (ft_parse_checks(vars, &i, tmp) == -255)
			return (-255);
		else if (ft_strncmp(&vars->str[i], "|", 1) == 0
			&& ft_get_type(vars->env, i) != ENVS)
		{
			tmp->next = ft_cmd_init();
			if (!tmp->next)
				ft_freevars_exit(vars, -1);
			tmp = tmp->next;
			i++;
		}
		else
			i += to_param_word(vars, tmp, i);
	}
	return (0);
}

/*
int	ft_parse_loop(t_vars *vars)
{
	t_cmd	*tmp;
	int		i;
	int		len;
	int		ret;

	len = ft_strlen(vars->str);
	tmp = vars->cmd;
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(&vars->str[i], " ", 1) == 0)
			i += skip_spaces(&vars->str[i]);
		else if (ft_strncmp(&vars->str[i], "\'", 1) == 0
			&& ft_get_type(vars->env, i) != ENVS)
		{
			ret = to_param_quote(vars, tmp, i) + 1;
			if (ret == -255)
				return (-255);
			i += ret;
		}
		else if (ft_strncmp(&vars->str[i], "\"", 1) == 0
			&& ft_get_type(vars->env, i) != ENVS)
		{
			ret = to_param_dblquote(vars, tmp, i) + 1;
			if (ret == -255)
				return (-255);
			i += ret;
		}
		else if (ft_strncmp(&vars->str[i], "|", 1) == 0
			&& ft_get_type(vars->env, i) != ENVS)
		{
			tmp->next = ft_cmd_init();
			if (!tmp->next)
				ft_freevars_exit(vars, -1);
			tmp = tmp->next;
			i++;
		}
		else if ((vars->str[i] == 60 || vars->str[i] == 62)
			&& ft_get_type(vars->env, i) != ENVS)
		{
			ret = to_redirect(vars, tmp, i);
			if (ret == -255)
				return (-255);
			i += ret;
		}
		else
			i += to_param_word(vars, tmp, i);
	}
	return (0);
}
*/

int	ft_parse_line(char *str, t_shell *shell)
{
	t_vars		vars;

	ft_init_vars(&vars, shell, str);
	ft_parse_quotes(&vars);
	ft_handle_dollars(&vars);
	if (ft_parse_loop(&vars) == -255)
		return (-255);
	free(vars.str);
	free_quotes_list(vars.quotes);
	free_quotes_list(vars.env);
	return (0);
}
