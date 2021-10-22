/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:42:04 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/22 11:29:16 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_build_newstr(t_vars *vars, t_quotes limits, char *tmp)
{
	char	*partA;
	char	*partB;
	char	*swap;
	char	*final;


	//rajouter les protections
	partA = ft_substr(vars->str, 0, limits.start);
	//ft_append_quote_data();
	partB = ft_substr(vars->str, limits.end, ft_strlen(vars->str));
	swap = ft_strjoin(partA, tmp);
	final = ft_strjoin(swap, partB);
	free(partA);
	free(partB);
	free(swap);
	return (final);
}

void	ft_env_expand_double(t_vars *vars, int *i)
{
	char		*tmp;
	char		*swap;
	t_quotes	limits;

	limits.start = *i;
	limits.end = ft_get_env_limit(vars->str, vars->quotes, *i);
	limits.type = NONE;
	limits.next = NULL;

	//printf("str:%s\n start: %d | size: %d |end: %d\n", vars->str, limits.start, limits.end - limits.start, limits.end);
	tmp = ft_substr(vars->str, limits.start + 1, limits.end - limits.start - 1);
	if (!tmp)
	{
		//free
	}
	//printf("tmp:%s\n", tmp);
	//printf("env:%s\n", getenv(tmp));
	swap = getenv(tmp);
	printf("old i:%d\n", *i);
	ft_update_quote_data(vars, (ft_strlen(swap) - ft_strlen(tmp)), *i);
	*i = *i + ft_strlen(swap) - 1;

	printf("new i:%d\n", *i);
	free(tmp);
	//printf("plop\n");
	tmp = ft_build_newstr(vars, limits, swap);
	//free(swap);
	free(vars->str);
	vars->str = tmp;
	printf("new str:%s\n", vars->str);
}

// void	ft_env_expand_none(t_cmd *cmd, char *str, t_quotes *quotes, int *i)
// {
// 	char		*tmp;
// 	t_quotes	limits;

// 	limits.start = *i;
// 	limits.end = ft_get_env_limit(str, quotes, *i);
// 	limits.type = NONE;
// 	limits.next = NULL;


// }

int		ft_get_env_limit(char *str, t_quotes *quotes, int i)
{
	i++;
	while(str[i])
	{
		printf("yo| i:%d | str[i]:%c\n", i, str[i]);
		if (is_separator(str[i]) || is_quote_or_dollar(str[i]))
		{
			printf("in the if de env limit\n");
			break ;
		}
		i++;
	}
	return (i);
}

void	ft_handle_dollars(t_vars *vars)
{
	int	i;
	t_type	type;

	i = 0;
	//printf("pikachu\n");
	while (vars->str[i])
	{
		printf("(dolls)i:%d | char: %c\n", i, vars->str[i]);
		if (vars->str[i] == (char) 36)
		{
			printf("dans le if 107\n");
			


t_quotes *tmp;
tmp = vars->quotes;
while (tmp)
{
	printf("start:%d | end:%d | type:%d\n", tmp->start, tmp->end, tmp->type);
	tmp = tmp->next;
}




			type = ft_get_type(vars->quotes, i);
			printf("type: %d\n", type);
			if (type == NONE)
			{

			}
			else if (type == DOUBLE)
			{
				ft_env_expand_double(vars, &i);
			}
		}
		i++;
	}




}