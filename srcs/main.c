/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:17:49 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 11:50:24 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/token.h"
#include <readline/readline.h>
//#include <readline/history.h>

int main()
{
	char*	line;
	t_list*	list;

	list = ft_list_init();
	while (1)
	{
		line = readline("Enter a line: ");
		ft_parse_line(line, list);
		free(line);
	}
	

	//printf("%s", line);
//	system(line);

	return 0;
}