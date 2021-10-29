NAME			= minishell

SRCSF			= exec_cmd.c \
				  get_cmd_path.c \
				  minishell.c \
				  here_doc.c \
				  param_utils.c \
				  redirect_handler.c \
				  utils.c \
				  exits.c \
				  tools.c \
				  main.c \
				  parse_tools.c \
				  parse_input.c  \
				  s_cmd.c \
				  echo.c \
				  s_env.c \
				  env.c \
				  pwd.c \
				  env_tools.c \
				  cd.c \
				  export.c \
				  set_prompt.c \
				  unset.c \
				  dollars.c \
				  s_vars.c \
				  debug.c \
				  s_quotes.c \
				  exit.c \
				  set_cmd.c


SRCS			= $(addprefix srcs/, ${SRCSF})

OBJS			= $(SRCS:.c=.o)

CC				= gcc

RM				= rm -f

CFLAGS			= -g3 #-fsanitize=address

all:			$(NAME)

%.o: 			%.c	headers/minishell.h libft/include/libft.h
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				make -C libft/
				$(CC) $(CFLAGS) \
				-L /Users/$$USER/.brew/opt/readline/lib \
				-I/Users/$$USER/.brew/opt/readline/include \
				-o $(NAME) $(OBJS) libft/libft.a -lreadline

clean:
				make clean -C libft/
				$(RM) $(OBJS)

fclean:			clean
				make fclean -C libft/
				$(RM) minishell
				make fclean -C libft/

re:				fclean all

.PHONY:			re fclean clean all