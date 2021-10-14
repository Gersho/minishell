SRCS		= srcs/exec_cmd.c srcs/get_cmd_path.c srcs/minishell.c srcs/redirect_handler.c srcs/utils.c srcs/exits.csrcs/main.c srcs/parse_input.c  srcs/s_cmd.c


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
				$(CC) $(CFLAGS) libft/libft.a -Iheaders/minishell.h -lreadline -L /Users/$$USER/.brew/opt/readline/lib -I/Users/$$USER/.brew/opt/readline/include -o $(NAME) $(OBJS)

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) minishell
				$(RM) libft/libft.a

re:			fclean all

.PHONY:		re fclean clean all