/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/29 00:02:43 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_param_loop(t_vars *vars, int *i)
{
	while (vars->str[*i])
	{
		//printf("paramloop i:%d | char:%c\n", *i, vars->str[*i]);
		if (is_separator(vars->str[*i]))
		{
			break ;
		}
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0)
		{
			*i += ft_str_index_c((&vars->str[*i] + 1), '\'') + 1;
		}
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0)
		{
			*i += ft_str_index_c((&vars->str[*i] + 1), '\"') + 1;
		}
		*i += 1;
	}
//	printf("going out\n");
}

int	to_param_quote(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	j = ft_str_index_c((vars->str + i + 1), '\'') + i + 2;
	if (j == 0)
	{
		//verifier valeur i si pas de closing quote (+2)
		//pas de closing quote
		printf("error: no closing quote\n");
	}
	ft_param_loop(vars, &j);

	//build selective substr

	//tmp = ft_substr(vars->str, i + 1, j - i - 2);
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);


	current->param = ft_param_append_word(vars, current->param, tmp);
	free(tmp);
	//printf("to param quote:(j-i):%d\n", j- i);
	return (j - i - 1);
}

int	to_param_dblquote(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	(void) vars;
	j = ft_str_index_c((vars->str + i + 1), '\"') + i + 2;
	//printf("i:%d --- j:%d\n", i, j);
	if (j == 0)
	{
		//pas de closing quote
		printf("error: no closing quote\n");
	}
	ft_param_loop(vars, &j);

	//printf("test:%s\n", vars->str + i);
	//tmp = ft_substr(vars->str, i + 1, j - i - 2);
//	printf("to param dble quote:i:%d ---j:%d\n", i, j);
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);


	//printf("tmp:%s\n", tmp);
	current->param = ft_param_append_word(vars, current->param, tmp);
	free(tmp);
	return (j - i - 1);
}

int	to_param_word(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;

	//(void) vars;
	j = i + 1;
	ft_param_loop(vars, &j);
	//printf("107 j:%d\n", j);
	//tmp = ft_substr(vars->str, i, j - i);
	tmp = ft_no_signifiant_quote_substr(vars, i, j - 1);
	//printf("tmp:%s*\n", tmp);
	current->param = ft_param_append_word(vars, current->param, tmp);
	free(tmp);
	return (j - i);
}


void	ft_red_loop(t_vars *vars, int *i)
{
	while (vars->str[*i])
	{
		//printf("redloop i:%d | char:%c\n", *i, vars->str[*i]);
		if (vars->str[*i] == 32 && ft_get_type(vars->env, *i) != ENVS)
			break ;
		if (vars->str[*i] == 62 || vars->str[*i] == 60 || vars->str[*i] == 124)
		{
			if (ft_get_type(vars->env, *i) == ENVS)
			{
				if (vars->str[*i] == 62 || vars->str[*i] == 60)
				{
				//ambiguous redirect ?
				printf("ambiguous redirect\n");
				//TODO clean exit
				exit(-1);
				}
				*i += 1;
				continue;
			}
			else
				break ;
		}
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0  && ft_get_type(vars->env, *i) != ENVS)
		{
			*i += ft_str_index_c((&vars->str[*i] + 1), '\'') + 1;
		}
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0 && ft_get_type(vars->env, *i) != ENVS)
		{
			*i += ft_str_index_c((&vars->str[*i] + 1), '\"') + 1;
		}
		*i += 1;
	}
//	printf("redloop going out\n");
}

int	to_redirect(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;
	char	*swap;

	j = i + 1;
	if (vars->str[j] == vars->str[j - 1])
		j++;
	j += skip_spaces(&vars->str[j]);

	ft_red_loop(vars, &j);

	tmp = ft_substr(vars->str, i, j - 1);
	if (current->red == NULL)
	{
		current->red = ft_strjoin("", tmp);
	}
	else
	{
		swap = current->red;
		current->red = ft_strjoin(swap, tmp);
		free(swap);
	}
	free(tmp);
	return (j);
}


/*


int	to_redirect(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	char	*tmp;
	char	*swap;

	j = 1;
	while (is_redirect_or_space(vars->str[j]))
		j++;
	while (!is_separator(vars->str[j]))
		j++;
	tmp = ft_substr(vars->str, 0, j);
	if (current->red == NULL)
	{
		current->red = ft_strjoin("", tmp);
	}
	else
	{
		swap = current->red;
		current->red = ft_strjoin(swap, tmp);
		free(swap);
	}
	free(tmp);
	return (j);
}

*/