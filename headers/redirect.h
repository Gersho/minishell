/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:43:35 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:43:35 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

void	redirect_handler(t_shell *shell);
int		here_doc(char *limiter, t_shell *shell);
int		which_redirect(char *red);

#endif
