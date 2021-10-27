/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/27 17:14:28 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_param_loop(t_vars *vars, int *i)
{
	t_quotes	tmp;

	while (vars->str[*i])
	{
		if (is_separator(vars->str[*i]))
		{
			break ;
		}
		else if (ft_strncmp(&vars->str[*i], "\'", 1) == 0)
		{
			//tmp.start = *i;
			*i += ft_str_index_c((&vars->str[*i] + 1), '\'') + 1;
			// tmp.end = *i - 1;
			// tmp.type = SIMPLE;
			// ft_append_quote_data(vars, vars->quotes, tmp);
		}
		else if (ft_strncmp(&vars->str[*i], "\"", 1) == 0)
		{
			//tmp.start = *i;
			*i += ft_str_index_c((&vars->str[*i] + 1), '\"') + 1;
			// tmp.end = *i - 1;
			// tmp.type = DOUBLE;
			// ft_append_quote_data(vars, vars->quotes, tmp);
		}
		*i += 1;
	}
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
	tmp = ft_no_signifiant_quote_substr(vars, i, j);


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
	printf("i:%d --- j:%d\n", i, j);
	if (j == 0)
	{
		//pas de closing quote
		printf("error: no closing quote\n");
	}
	ft_param_loop(vars, &j);

	printf("test:%s\n", vars->str + i);
	//tmp = ft_substr(vars->str, i + 1, j - i - 2);
//	printf("to param dble quote:i:%d ---j:%d\n", i, j);
	tmp = ft_no_signifiant_quote_substr(vars, i, j);


	//printf("tmp:%s\n", tmp);
	current->param = ft_param_append_word(vars, current->param, tmp);
	free(tmp);
	return (j - i - 1);
}

int	to_param_word(t_vars *vars, t_cmd *current, char *str)
{
	int		i;
	char	*tmp;

	(void) vars;
	i = 1;
	ft_param_loop(vars, &i);
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(vars, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_redirect(t_vars *vars, t_cmd *current, char *str)
{
	int		i;
	char	*tmp;
	char	*swap;

	(void) vars;
	i = 1;
	while (is_redirect_or_space(str[i]))
		i++;
	while (!is_separator(str[i]))
		i++;
	tmp = ft_substr(str, 0, i);
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
	return (i);
}
