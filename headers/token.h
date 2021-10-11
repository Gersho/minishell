/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:39:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/11 16:15:06 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H_
#define TOKEN_H_

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

typedef struct	s_cmd	t_cmd;
typedef struct	s_red	t_red;
typedef struct	s_list	t_list;
typedef enum	e_token	t_token;

enum	e_token
{
	DBL_QUOTE,
	SMP_QUOTE,
	DOLLAR,
	CHEV_LEFT,
	CHEV_RIGHT,
	DBL_LEFT,
	DBL_RIGHT,
	COMMAND,
	NONE
};

struct s_list
{
	t_cmd*		cmd;
	t_red*		red;
	t_list*		next;

};

struct	s_cmd
{
	char**		str;
	t_token		token;
	t_cmd*		next;
};

struct s_red
{
	char**		str;
	t_red*		next;
};


t_list	*ft_list_init();
t_cmd	*ft_cmd_init(t_list *list);
t_red	*ft_red_init(t_list *list);

void	ft_parse_line(char *line, t_list *list);

void	ft_error_exit(int err);
void	ft_freestructs_exit(t_list* list, int err);

#endif