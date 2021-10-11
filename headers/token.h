/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:39:57 by kzennoun          #+#    #+#             */
/*   Updated: 2021/10/09 14:52:47 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H_
#define TOKEN_H_


typedef enum	e_token
{
	DBL_QUOTE,
	SMP_QUOTE,
	DOLLAR,
	PIPE,
	CHEV_LEFT,
	CHEV_RIGHT,
	DBL_LEFT,
	DBL_RIGHT,
	COMMAND
}				t_token;

typedef struct	s_link
{
	char**		str;
	t_token		token;
	t_link*		next;
}				t_link;



#endif