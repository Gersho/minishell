/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/02 14:41:51 by kzennoun         ###   ########lyon.fr   */
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


int	ft_red_loop(t_vars *vars, int *i)
{
	if (is_separator(vars->str[*i]))
	{
		//unexpeced
		ft_printf_fd(2, "%s: syntax error near unexpected token '%c'\n", PROMPTERR, vars->str[*i]);
		*vars->last_ret = 258;
		return (-255);
	}
	else if (vars->str[*i] == '\0')
	{
		ft_printf_fd(2, "%s: syntax error near unexpected token 'newline'\n", PROMPTERR);
		*vars->last_ret = 258;
		return (-255);
	}
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
	return (0);
}

int	to_redirect(t_vars *vars, t_cmd *current, int i)
{
	int		j;
	int		k;
	char	*tmp;

	//get red symbols
	j = i + 1;
	if (vars->str[j] == vars->str[j - 1])
		j++;
	tmp = ft_substr(vars->str, i, j- i);
	current->red = ft_param_append_word(vars, current->red, tmp);

	//get the red
	j += skip_spaces(&vars->str[j]);

	k = j;


	//ft_param_loop(vars, &k);
	if (ft_red_loop(vars, &k) == -255)
	{
		return (-255);
	}

	//printf("after redloop j:%d*\n", j);
	tmp = ft_no_signifiant_quote_substr(vars, j, k - 1);
	//printf("tmp:%s*\n", tmp);
	//tmp = ft_substr(vars->str, i, k- i);
	current->red = ft_param_append_word(vars, current->red, tmp);
	free(tmp);
	return (k - i);
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