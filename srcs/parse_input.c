/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/27 12:46:42 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_parse_loop(t_vars *vars)
{
	t_cmd	*tmp;
	int		i;
	int		len;

	len = ft_strlen(vars->str);
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
	t_vars		vars;

	ft_init_vars(&vars, cmd, str);

	ft_parse_quotes(&vars);
	ft_handle_dollars(&vars);

	printf("str after dolls:%s\n", vars.str);
	ft_debug_quotes_env(&vars);
	
	//exit(0);


	
	ft_parse_loop(&vars);



	//free stuff from vars
	free(vars.str);
}
