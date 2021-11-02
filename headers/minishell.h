/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:39:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/31 02:06:45 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>

typedef struct s_cmd				t_cmd;
typedef enum e_type					t_type;
typedef struct s_quotes				t_quotes;
typedef struct s_vars				t_vars;
typedef struct s_shell				t_shell;

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
# define PROMPTERR "💢"

typedef struct	s_env_list t_env;

enum e_cmd_name
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_open_param
{
	RED_OUT_T,
	RED_OUT_A,
	RED_IN,
	HERE_DOC
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
	char*		path;
	char**		param;
	char**		red;
	int 		in;
	int 		out;
	t_cmd*		next;
};

struct s_vars
{
	t_cmd		*cmd;
	t_quotes	*quotes;
	t_quotes	*env;
	t_env		*env_vars;
	char		*str;
	int			last_ret;
};


struct s_env_list
{
	char	*name;
	char	*value;
	t_env	*prev;
	t_env	*next;
};

struct s_shell
{
	t_cmd	*cmd;
	t_env 	*env;
	int		std_out;
	int 	std_in;
	int 	ret;
	int		error;
};

//----list_cmd
t_cmd	*ft_cmd_init();
t_cmd	*ft_cmd_last(t_cmd *cmd);
void	ft_cmd_addback(t_cmd *start, t_cmd *new);
size_t	ft_size_list(t_cmd *cmd_list);
void	free_cmd_list(t_cmd *cmd);
//----env_tools
t_env	*get_env_list(char **env_main);
int		env_seeker(t_env **env_l, const char *name);
char	**get_env_tab(t_env *env);
void	env_ch_value(t_env *old, char *new);
//----list_env
char	**init_env_tab(char **env);
int		env_list_size(t_env *env);
void	free_env_list(t_env *env);
void	print_list(t_env *env);
t_env	*new_env(char *name, char *value);
void	env_add_back(t_env **lst, t_env *new);
t_env	*env_last(t_env *env);
t_env	*env_dup(t_env *env);
t_env 	*env_unlink(t_env *env_l, char *name);
//----cmd->param
char	**ft_param_init(t_cmd* cmd);
char	**ft_param_append_word(t_vars *vars, char** param, char* new);
int		to_param_quote(t_vars *vars, t_cmd *current, int i);
int		to_param_dblquote(t_vars *vars, t_cmd *current, int i);
int		to_param_word(t_vars *vars, t_cmd *current, int i);
int		to_redirect(t_vars *vars, t_cmd *current, int i);
//----s_quotes
t_quotes	*ft_quotes_init(t_vars *vars, int start, int end, t_type type);
void		ft_parse_quotes(t_vars *vars);
void		ft_append_quote_data(t_vars *vars, t_quotes *quotes, t_quotes tmp);
t_type		ft_get_type(t_quotes *quotes, int i);
void		ft_update_quote_data(t_vars *vars, t_quotes *quotes, int size, int i);
int			ft_get_quote_count(t_vars *vars, int start, int end);
int			ft_is_quote_data(t_vars *vars, int i);
//----s_vars
void	ft_init_vars(t_vars *vars, t_shell *shell, char *str);
//----env expand
void	ft_handle_dollars(t_vars *vars);
void	ft_env_expand_double(t_vars *vars, int *i);
void	ft_env_expand_none(t_vars *vars, int *i);
int		ft_get_env_limit(char *str, int i);
char 	*ft_get_env_value(t_vars *vars, char *name);
//----Parsing
void	ft_parse_line(char *line, t_shell *shell);
void	ft_parse_loop(t_vars *vars);
//----Error handling
void	ft_error_exit(int err);
void	ft_freestructs_exit(t_vars *vars, int err);
//----Utils
int		skip_spaces(char *str);
void	close_perror(int fd);
void	dup2_close(int fd1, int fd2);
void	close_fds(int nb, ...);
char	*str_in_lower_case(char *s);
//----Tools
int		ft_str_index_c(char *str, char c);
int		is_separator(char c);
int		is_redirect_or_space(char c);
int		is_quote_or_dollar(char c);
char	*rm_redundant_spaces(t_vars *vars, char *str);
char	*ft_no_signifiant_quote_substr(t_vars *vars, int start, int end);
//----Get cmd path
char	**split_env_path(t_env *envp);
int		get_cmd_path(t_cmd *cmd, char **path_tab);
//----Redirect Handling
void	redirect_handler(t_shell *shell);
int		is_redirect(char c);
int 	here_doc(char* limiter, t_cmd *cmd);
//----Exec command
int 	exec_cmd(t_shell *shell);
int		check_built_in(t_shell *shell);
//----COMMANDS BUILT IN
int 	echo(char **param);
int 	pwd(char **param, t_env *env_l);
int 	cd(char **param, t_env *env_l);
int 	env(t_env *env_l);
int 	export(char **param, t_env **env);
int 	unset(char **param, t_env **env_l);
void 	exit_shell(t_cmd *cmd, t_env *env);
//----SET CMD
//----PROMPT
char 	*set_prompt(t_shell *shell);
//debug
void ft_debug_quotes_env(t_vars *vars);
#endif