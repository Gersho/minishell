/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:31:35 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/15 12:37:53 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


char	**ft_param_init(t_cmd* cmd)
{
	char**	tmp;

	tmp = malloc(sizeof(char*));
	if (!tmp)
		ft_freestructs_exit(cmd, -1);
	tmp[0] = NULL;
	return tmp;	
}

//cmd root au cas ou pour free
//param du current cmd->param
//new char* a append sur cmd->param
//returns ptr to new char** (previous char** free'd)
char	**ft_param_append_word(t_cmd* cmd, char** param, char* new)
{
	int i;
	char**	tmp;

	i = 0;
	while (param[i] != NULL)
		i++;
	tmp = malloc(sizeof(char*) * (i+ 2));
	if (!tmp)
		ft_freestructs_exit(cmd, -1);
	i = 0;
	while (param[i] != NULL)
	{
		tmp[i] = ft_strdup(param[i]);
		if (!tmp[i])
		{
			ft_free_str_tab(tmp);
			ft_freestructs_exit(cmd, -1);
		}
		i++;
	}
	tmp[i] = ft_strdup(new);
	if (!tmp[i])
	{
		ft_free_str_tab(tmp);
		ft_freestructs_exit(cmd, -1);
	}
	tmp[i+1] = NULL;
	ft_free_str_tab(param);
	return tmp;
}

/*
int main(void)
{
	char** test;

	test = ft_param_init(NULL);
	test = ft_param_append_word(NULL, test, "coucou");
	test = ft_param_append_word(NULL, test, "allo");
	test = ft_param_append_word(NULL, test, "vive le couscous");


	printf("test0: %s\n", test[0]);
	printf("test1: %s\n", test[1]);
	printf("test2: %s\n", test[2]);
	printf("test3: %s\n", test[3]);
	// printf("test4: %s\n", test[4]);
	// printf("test5: %s\n", test[5]);

}
*/