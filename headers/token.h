/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:39:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/12 15:20:01 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H_
#define TOKEN_H_

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

typedef struct	s_args	t_args;
typedef struct	s_cmd	t_cmd;


enum e_open_param
{
	RED_OUT_T,
	RED_OUT_A,
};

struct s_cmd
{
	char*		path;
	char**		param_tab;
	t_args*		param;
	t_args*		red;
	t_cmd*		next;

};

struct	s_args
{
	char*		str;
	t_args*		next;
};

//----lst_cmd
t_cmd	*ft_cmd_init();
t_cmd	*ft_cmd_last(t_cmd *cmd);
void	ft_cmd_addback(t_cmd *start, t_cmd *new);
size_t	ft_size_list(t_args *arg_list);

t_args	*ft_args_init(t_cmd *cmd, char* str);
t_args	*ft_args_last(t_args *args);
void	ft_args_addback(t_args *start, t_args *new);

void	ft_parse_line(char *line, t_cmd *list);

void	ft_error_exit(int err);
void	ft_freestructs_exit(t_cmd* list, int err);

#endif