/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:46:43 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 09:46:45 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

typedef struct s_cmd		t_cmd;
typedef enum e_type			t_type;
typedef struct s_quotes		t_quotes;
typedef struct s_vars		t_vars;
typedef struct s_shell		t_shell;
typedef struct s_env_list	t_env;

enum e_open_param
{
	HERE_DOC,
	RED_OUT_T,
	RED_OUT_A,
	RED_IN
};

enum e_type
{
	SIMPLE,
	DOUBLE,
	NONE,
	ENVS
};

struct s_quotes
{
	int			start;
	int			end;
	t_type		type;
	t_quotes	*next;
};

struct s_cmd
{
	int		pid;
	char	*path;
	char	**param;
	char	**red;
	int		in;
	int		out;
	t_cmd	*next;
};

struct s_vars
{
	t_cmd		*cmd;
	t_quotes	*quotes;
	t_quotes	*env;
	t_env		*env_vars;
	char		*str;
	int			*last_ret;
};

struct s_shell
{
	t_cmd			*cmd;
	t_env			*env;
	int				std_out;
	int				std_in;
	int				ret;
	int				error;
	struct termios	term;
};

#endif
