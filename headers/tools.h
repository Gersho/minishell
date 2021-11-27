/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:42 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/27 11:32:11 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "minishell.h"

/*	CLOSE_TOOLS	*/
void	close_perror(int fd);
void	dup2_close(int fd1, int fd2);
void	close_multiple_fd(int nb, ...);
void	close_unused_fd(t_shell *shell, int pipe_in);
void	close_all_fds(t_cmd *cmd);

/*	ENV_TOOLS	*/
int		env_seeker(t_env **env_l, const char *name);
char	**get_env_tab(t_env *env_l);
void	env_ch_value(t_env *old, char *new);
t_env	*get_env_list(char **env_main);

/*	UTILS	*/
char	*ft_mega_str_join(int nb, ...);
char	*str_in_lower_case(char *s);
void	print_error_prompt(char *str);
int		skip_spaces(char *str);
void	replace_std(int in, int out);
char	*lltoa(long long nb);
void	free_all(t_shell *shell, int display_err_and_exit, char *err_name);

#endif
