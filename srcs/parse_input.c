/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:10:29 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/02 14:55:43 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

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
		//printf("cur i: %d --- cur c:%c\n", i, vars->str[i]);
		if (ft_strncmp(&vars->str[i], " ", 1) == 0)
			i += skip_spaces(&vars->str[i]);
		else if (ft_strncmp(&vars->str[i], "\'", 1) == 0 && ft_get_type(vars->env, i) != ENVS)
			i += to_param_quote(vars, tmp, i) + 1;
		else if (ft_strncmp(&vars->str[i], "\"", 1) == 0 && ft_get_type(vars->env, i) != ENVS)
			i += to_param_dblquote(vars, tmp, i) + 1;
		else if (ft_strncmp(&vars->str[i], "|", 1) == 0 && ft_get_type(vars->env, i) != ENVS)
		{
			tmp->next = ft_cmd_init();
			tmp = tmp->next;
			i++;
		}
		else if ((vars->str[i] == 60 || vars->str[i] == 62) && ft_get_type(vars->env, i) != ENVS)
		{
			ret = to_redirect(vars, tmp, i);
			if (ret == -255)
			{
				//TODO free
				return (-255);
			}

			i += to_redirect(vars, tmp, i);
			
		}
		else
		{
			//printf("else word i before:%d | ", i);
			i += to_param_word(vars, tmp, i);
			//printf("i after: %d\n", i);
		}
	}
	return (0);
}

int	ft_parse_line(char *str, t_shell *shell)
{
	t_vars		vars;

	ft_init_vars(&vars, shell, str);

	ft_parse_quotes(&vars);
	ft_handle_dollars(&vars);

	//printf("%s*:str after dolls\n", vars.str);
	//ft_debug_quotes_env(&vars);
	
	//exit(0);


	if (ft_parse_loop(&vars) == -255)
	{
		return (-255);
	}

	//ft_parse_loop(&vars);


	//free stuff from vars
//	printf("line=%s\n", vars.str);
	free(vars.str);
	return (0);
}
