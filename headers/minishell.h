/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:39:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/15 16:03:37 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H_
#define MINISHELL_H_

# include "../libft/include/libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <readline/readline.h>

typedef struct	s_cmd	t_cmd;
typedef struct	s_file_descriptors	t_fds;
enum e_cmd_name
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};//probably useless but we never know

enum e_open_param
{
	RED_OUT_T,
	RED_OUT_A,
	RED_IN,
	HERE_DOC
};

struct s_cmd
{
	char*		path;
	char**		param;
	char*		red;
	t_fds		*fd;
	t_cmd*		next;
};

struct s_file_descriptors
{
	int std_out;
	int std_in;
	int pipe[2];
	int prev_pipe_in;
};

//----lst_cmd
t_cmd	*ft_cmd_init();
t_cmd	*ft_cmd_last(t_cmd *cmd);
void	ft_cmd_addback(t_cmd *start, t_cmd *new);
size_t	ft_size_list(t_cmd *cmd_list);
//----cmd->param
char	**ft_param_init(t_cmd* cmd);
char	**ft_param_append_word(t_cmd* cmd, char** param, char* new);
int		to_param_quote(t_cmd *forfree, t_cmd *current, char* str);
int		to_param_dblquote(t_cmd *forfree, t_cmd *current, char* str);
int		to_param_word(t_cmd *forfree, t_cmd *current, char* str);

//----Parsing
void	ft_parse_line(char *line, t_cmd *list);
//----Error handling
void	ft_error_exit(int err);
void	ft_freestructs_exit(t_cmd* list, int err);
//----Utils
int		skip_spaces(char *str);
void	close_perror(int fd);
void	dup2_close(int fd1, int fd2);
void	close_fds(int nb, ...);
char	*str_in_lower_case(char *s);
//----Tools
int		ft_str_index_c(char *str, char c);
int		is_separator(char c);
//----Get cmd path
char	**split_env_path(char **envp);
int		get_cmd_path(t_cmd *cmd, char **path_tab);
//----Redirect Handling
int		redirect_handler(char *red, t_cmd *cmd);
int		is_redirect(char c);
int 	here_doc(char* limiter, t_cmd *cmd);
//----Exec command
int		exec_cmd(t_cmd *cmd, char **env);
//----COMMANDS BUILT IN
void	check_built_in(char **param);
void	echo(char **param);

#endif