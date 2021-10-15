/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:09:37 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/15 17:25:13 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	to_param_quote(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = ft_str_index_c((str + 1), '\'') + 2;
	if (i == -1)
	{
		//pas de closing quote
		printf("error: no closing quote\n");
	}
	//printf("L26 - i : %d -- str[i] = %c\n", i, str[i]);
	while (str[i])
	{
		// printf("L29 - i : %d -- str[i] = %c\n", i, str[i]);
		if (is_separator(str[i]))
		{
			// printf("break because - i : %d -- str[i] = %c  (int) %d\n", i, str[i], (int)str[i]);
			// printf("rest of str:%s\n", &str[i]);
			break;
		}
		else if (ft_strncmp(&str[i], "\'", 1) == 0)
		{
			// printf("smp\n");
			i += ft_str_index_c((&str[i] + 1), '\'') + 1;
		}
		else if (ft_strncmp(&str[i], "\"", 1) == 0)
		{
			// printf("dbl\n");
			i += ft_str_index_c((&str[i] + 1), '\"') + 1;
		}
		i++;
	}
	tmp = ft_substr(str, 0, i);
	// printf("tmp: %s\n", tmp);
	//if dollar ??
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_param_dblquote(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = ft_str_index_c((str + 1), '\"') + 2;
	if (i == -1)
	{
		//pas de closing quote
		printf("error: no closing quote\n");
	}
	//printf("L26 - i : %d -- str[i] = %c\n", i, str[i]);
	while (str[i])
	{
		// printf("L29 - i : %d -- str[i] = %c\n", i, str[i]);
		if (is_separator(str[i]))
		{
			// printf("break because - i : %d -- str[i] = %c  (int) %d\n", i, str[i], (int)str[i]);
			// printf("rest of str:%s\n", &str[i]);
			break;
		}
		else if (ft_strncmp(&str[i], "\'", 1) == 0)
		{
			// printf("smp\n");
			i += ft_str_index_c((&str[i] + 1), '\'') + 1;
		}
		else if (ft_strncmp(&str[i], "\"", 1) == 0)
		{
			// printf("dbl\n");
			i += ft_str_index_c((&str[i] + 1), '\"') + 1;
		}
		i++;
	}
	tmp = ft_substr(str, 0, i);
	// printf("tmp: %s\n", tmp);
	//if dollar ??
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}

int	to_param_word(t_cmd *forfree, t_cmd *current, char* str)
{
	int i;
	char *tmp;

	i = 1;
	while (str[i])
	{
		// printf("L29 - i : %d -- str[i] = %c\n", i, str[i]);
		if (is_separator(str[i]))
		{
			// printf("break because - i : %d -- str[i] = %c  (int) %d\n", i, str[i], (int)str[i]);
			// printf("rest of str:%s\n", &str[i]);
			break;
		}
		else if (ft_strncmp(&str[i], "\'", 1) == 0)
		{
			// printf("smp\n");
			i += ft_str_index_c((&str[i] + 1), '\'') + 1;
		}
		else if (ft_strncmp(&str[i], "\"", 1) == 0)
		{
			// printf("dbl\n");
			i += ft_str_index_c((&str[i] + 1), '\"') + 1;
		}
		i++;
	}



	//i = ft_str_index_c(str, ' ');
	// if (i == -1)
	// 	i = ft_strlen(str);
	tmp = ft_substr(str, 0, i);
	current->param = ft_param_append_word(forfree, current->param, tmp);
	free(tmp);
	return (i);
}