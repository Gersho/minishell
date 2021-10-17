/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/17 13:05:11 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	ft_param_loop(char *str, int *i)
{
	while (str[*i])
	{
		if (is_separator(str[*i]))
		{
			break ;
		}
		else if (ft_strncmp(&str[*i], "\'", 1) == 0)
		{
			*i += ft_str_index_c((&str[*i] + 1), '\'') + 1;
		}
		else if (ft_strncmp(&str[*i], "\"", 1) == 0)
		{
			*i += ft_str_index_c((&str[*i] + 1), '\"') + 1;
		}
		*i += 1;
	}
}

int	to_param_quote(t_cmd *forfree, t_cmd *current, char *str)
{
	int		i;
	char	*tmp;

	i = ft_str_index_c((str + 1), '\'') + 2;
	if (i == -1)
	{
		//pas de closing quote
		printf("error: no closing quote\n");
	}
	ft_param_loop(str, &i);
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_param_dblquote(t_cmd *forfree, t_cmd *current, char *str)
{
	int		i;
	char	*tmp;

	i = ft_str_index_c((str + 1), '\"') + 2;
	if (i == -1)
	{
		//pas de closing quote
		printf("error: no closing quote\n");
	}
	ft_param_loop(str, &i);
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_param_word(t_cmd *forfree, t_cmd *current, char *str)
{
	int		i;
	char	*tmp;

	i = 1;
	ft_param_loop(str, &i);
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_redirect(t_cmd *forfree, t_cmd *current, char *str)
{
	int		i;
	char	*tmp;
	char	*swap;

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