SRCS		= srcs/exec_cmd.c srcs/get_cmd_path.c srcs/minishell.c srcs/here_doc.c srcs/param_utils.c srcs/redirect_handler.c srcs/utils.c srcs/exits.c srcs/tools.c srcs/main.c srcs/parse_tools.c srcs/parse_input.c  srcs/s_cmd.c srcs/echo.c 


OBJS			= $(SRCS:.c=.o)

NAME			= minishell
CC				= gcc
RM				= rm -f
CFLAGS			= -g

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