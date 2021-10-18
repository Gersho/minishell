SRCS		= srcs/dollars.c srcs/exec_cmd.c srcs/echo.c srcs/get_cmd_path.c srcs/here_doc.c srcs/minishell.c srcs/redirect_handler.c srcs/utils.c srcs/exits.c srcs/main.c srcs/parse_input.c srcs/param_utils.c srcs/tools.c srcs/parse_tools.c srcs/s_cmd.c


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
				make fclean -C libft/
				$(RM) minishell

re:			fclean all

.PHONY:		re fclean clean all