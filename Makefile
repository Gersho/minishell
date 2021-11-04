NAME			= minishell

BUILT_IN_F		= echo.c \
				  env.c \
				  pwd.c \
				  cd.c \
				  export.c \
				  unset.c \
				  exit.c

PARSING_F		= debug.c \
				  dollars.c \
				  exits.c \
				  parse_tools.c \
				  parse_input.c  \
				  s_cmd.c \
  				  tools.c \
				  param_utils.c \
				  s_vars.c \
				  s_quotes.c \

SRCSF			= exec_cmd.c \
				  get_cmd_path.c \
				  minishell.c \
				  here_doc.c \
				  redirect_handler.c \
				  utils.c \
				  main.c \
				  s_env.c \
				  env_tools.c \
				  set_prompt.c \
				  set_cmd.c


SRCS			= $(addprefix srcs/, $(SRCSF)) \
				  $(addprefix srcs/Built_in/, $(BUILT_IN_F)) \
				  $(addprefix srcs/Parsing/, $(PARSING_F))

OBJS			= $(SRCS:.c=.o)

CC				= gcc

RM				= rm -f

CFLAGS			= -g3 -fsanitize=address #-Wall -Wextra -Werror

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