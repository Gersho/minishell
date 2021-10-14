SRCS		= srcs/main.c srcs/exits.c srcs/list_init.c srcs/token.c srcs/parse_input.c


OBJS			= $(SRCS:.c=.o)

NAME			= minishell
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

all:			$(NAME)

%.o: 			%.c	headers/minishell.h
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS) headers/minishell.h
				make -C libft/
				$(CC) $(CFLAGS) -Iheaders/token.h -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include -o $(NAME) $(OBJS)

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) minishell

re:			fclean all

.PHONY:		re fclean clean all