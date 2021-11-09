/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:39:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/06 10:52:44 by kzennoun         ###   ########lyon.fr   */
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
# include <sys/wait.h>
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

//----list_cmd
t_cmd		*ft_cmd_init(void);
t_cmd		*ft_cmd_last(t_cmd *cmd);
void		ft_cmd_addback(t_cmd *start, t_cmd *new);
size_t		ft_size_list(t_cmd *cmd_list);
void		free_cmd_list(t_cmd *cmd);

//----list_env
char		**init_env_tab(char **env);
int			env_list_size(t_env *env);
void		free_env_list(t_env *env);
void		print_list(t_env *env);
t_env		*new_env(char *name, char *value);
void		env_add_back(t_env **lst, t_env *new);
t_env		*env_last(t_env *env);
t_env		*env_dup(t_env *env);
t_env		*env_unlink(t_env *env_l, char *name);
//----cmd->param
char		**ft_param_init(void);
char		**ft_param_append_word(char **param, char *new);
int			to_param_quote(t_vars *vars, t_cmd *current, int i);
int			to_param_dblquote(t_vars *vars, t_cmd *current, int i);
int			to_param_word(t_vars *vars, t_cmd *current, int i);
int			to_redirect(t_vars *vars, t_cmd *current, int i);
//----s_quotes
t_quotes	*ft_quotes_init(int start, int end, t_type type);
void		ft_parse_quotes(t_vars *vars);
void		ft_append_quote_data(t_vars *vars, t_quotes *quotes, t_quotes tmp);
t_type		ft_get_type(t_quotes *quotes, int i);
void		ft_update_quote_data(t_quotes *q, int size, int i);
void		free_quotes_list(t_quotes *quotes);
//----s_vars
void		ft_init_vars(t_vars *vars, t_shell *shell, char *str);
void		ft_free_vars(t_vars *vars);
//----env expand
void		ft_handle_dollars(t_vars *vars);
void		ft_env_expand_double(t_vars *vars, int *i);
void		ft_env_expand_none(t_vars *vars, int *i);
int			ft_get_env_limit(char *str, int i);
char		*ft_get_env_value(t_vars *vars, char *name);
//----parsing
int			ft_parse_line(char *line, t_shell *shell);
int			ft_parse_loop(t_vars *vars);
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
void		redirect_handler(t_shell *shell);
int			is_redirect(char c);
int			here_doc(char *limiter, t_cmd *cmd);
int			which_redirect(char *red);

//----PROMPT
char		*set_prompt(t_shell *shell);
//debug
void		ft_debug_quotes_env(t_vars *vars);
void		ft_debug_cmd(t_cmd *cmd);
#endif