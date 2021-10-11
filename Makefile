SRCS		= src/main.c src/exits.c src/parse.c src/token.c


OBJS			= $(SRCS:.c=.o)

NAME			= minishell
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

all:			$(NAME)

%.o: 			%.c	headers/token.h
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS) headers/token.h
				$(CC) $(CFLAGS) -Iheaders/token.h -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include -o $(NAME) $(OBJS)

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) minishell

re:			fclean all

.PHONY:		re fclean clean all