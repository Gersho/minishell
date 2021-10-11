SRCS		= main.test.c


OBJS			= $(SRCS:.c=.o)

NAME			= minishell
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

all:			$(NAME)

%.o: 			%.c	token.h
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS) token.h
				$(CC) $(CFLAGS) -Iheaders/token.h -o $(NAME) $(OBJS)

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) minishell

re:			fclean all

.PHONY:		re fclean clean all