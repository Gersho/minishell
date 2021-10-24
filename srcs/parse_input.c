/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/24 16:14:03 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_parse_loop(t_vars *vars, int len)
{
	t_cmd	*tmp;
	int		i;

	tmp = vars->cmd;
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(&vars->str[i], " ", 1) == 0)
			i += skip_spaces(&vars->str[i]);
		else if (ft_strncmp(&vars->str[i], "\'", 1) == 0 && ft_get_type(vars->env, i) != ENVS)
			i += to_param_quote(vars->cmd, tmp, &vars->str[i + 1]) + 1;
		else if (ft_strncmp(&vars->str[i], "\"", 1) == 0 && ft_get_type(vars->env, i) != ENVS)
			i += to_param_dblquote(vars->cmd, tmp, &vars->str[i + 1]) + 1;
		else if (ft_strncmp(&vars->str[i], "|", 1) == 0 && ft_get_type(vars->env, i) != ENVS)
		{
			tmp->next = ft_cmd_init();
			tmp = tmp->next;
			i++;
		}
		else if ((vars->str[i] == 60 || vars->str[i] == 62) && ft_get_type(vars->env, i) != ENVS)
			i += to_redirect(vars->cmd, tmp, &vars->str[i]);
		else
			i += to_param_word(vars->cmd, tmp, &vars->str[i]);
	}
}

void	ft_parse_line(char *str, t_cmd *cmd)
{
	int			len;
	t_vars		vars;

	vars.cmd = cmd;
	vars.str = str;
	len = ft_strlen(str);
	vars.quotes = ft_quotes_init(&vars, -1, -1, NONE);
	vars.env = ft_quotes_init(&vars, -1, -1, NONE);
	if (!vars.quotes)
	{
		//todo free
	}
	ft_parse_quotes(&vars, str, len, vars.quotes);


	//ft_debug_quotes_env(&vars);


	ft_handle_dollars(&vars);

	//exit(-2);
	printf("str after dolls:%s\n", vars.str);
	len = ft_strlen(vars.str);
	ft_parse_loop(&vars, len);

}
