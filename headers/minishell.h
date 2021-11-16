/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:39:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/13 15:03:54 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define PROMPTERR "💢"

# include <termios.h>
# include "shell_struct.h"
# include "../libft/include/libft.h"
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include "built_in.h"
# include "exec_cmd.h"
# include "redirect.h"
# include "env_list.h"
# include "tools.h"
# include "signals.h"
# include "parsing.h"

extern	int*	g_ptr;

//----list_cmd
t_cmd		*ft_cmd_init(void);
t_cmd		*ft_cmd_last(t_cmd *cmd);
void		ft_cmd_addback(t_cmd *start, t_cmd *new);
size_t		ft_size_list(t_cmd *cmd_list);
void		free_cmd_list(t_cmd *cmd);
//----list_env
char		**init_env_tab(char **env);
//----Error handling
void		ft_error_exit(int err);
void		ft_freevars_exit(t_vars *vars);
//----Utils
int			skip_spaces(char *str);
void		print_error_prompt(char *str);
char		*str_in_lower_case(char *s);
//----Tools
int			ft_str_index_c(char *str, char c);
int			is_separator(char c);
int			is_redirect_or_space(char c);
int			is_quote_or_dollar(char c);
char		*rm_redundant_spaces(char *str);
char		*ft_no_signifiant_quote_substr(t_vars *vars, int start, int end);
//----redirect Handling
int			is_redirect(char c);
//----PROMPT
char		*set_prompt(t_shell *shell);
#endif