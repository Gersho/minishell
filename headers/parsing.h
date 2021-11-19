/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:39:23 by kzennoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:17:23 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

//----s_quotes
t_quotes	*ft_quotes_init(int start, int end, t_type type);
void		ft_append_quote_data(t_vars *vars, t_quotes *quotes, t_quotes tmp);
t_type		ft_get_type(t_quotes *quotes, int i);
void		ft_update_quote_data(t_quotes *q, int size, int i);
void		free_quotes_list(t_quotes *quotes);
void		ft_parse_quotes(t_vars *vars, int len);
//----s_vars
void		ft_init_vars(t_vars *vars, t_shell *shell, char *str);
void		ft_free_vars(t_vars *vars);
void		ft_free_vars_continue(t_vars *vars);
//----env expand
void		ft_handle_dollars(t_vars *vars, int len);
void		ft_env_expand_double(t_vars *vars, int *i);
void		ft_env_expand_none(t_vars *vars, int *i);
char		*ft_get_env_value(t_vars *vars, char *name);
//----parsing
int			ft_parse_line(char *line, t_shell *shell);
int			parse_error_quote(t_vars *vars);
int			ft_handle_pipe(t_vars *vars, int i, int len, t_cmd **tmp);
//----cmd->param
char		**ft_param_init(void);
char		**ft_param_append_word(char **param, char *new);
int			to_param_quote(t_vars *vars, t_cmd *current, int i);
int			to_param_dblquote(t_vars *vars, t_cmd *current, int i);
int			to_param_word(t_vars *vars, t_cmd *current, int i);
int			to_redirect(t_vars *vars, t_cmd *current, int i);
//----debug
void		ft_debug_quotes_env(t_vars *vars);
void		ft_debug_cmd(t_cmd *cmd);

#endif