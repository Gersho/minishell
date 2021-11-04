NAME			= minishell

HEADERS			= headers/minishell.h \
				  headers/built_in.h \
				  headers/exec_cmd.h \
				  headers/tools.h \
				  libft/include/libft.h

BUILT_IN		= echo.c \
				  env.c \
				  pwd.c \
				  cd.c \
				  export.c \
				  unset.c \
				  exit.c

EXEC_CMD		= parse_cmd.c \
                  cmd_launcher.c \
                  exec_built_in.c \
                  exec_cmd_fork.c \
                  get_cmd_path.c \
                  split_env_path.c

PARSING			= debug.c \
				  dollars.c \
				  exits.c \
				  parse_tools.c \
				  parse_input.c  \
				  s_cmd.c \
  				  tools.c \
				  param_utils.c \
				  s_vars.c \
				  s_quotes.c \

SRCSF			= env_tools.c \
				  main.c \
				  minishell.c \
				  s_env.c \
				  set_prompt.c \
				  utils.c

TOOLBOX			= close_tools.c

REDIRECT		= here_doc.c \
                  redirect_handler.c \
                  redirect_tools.c


SRCS			= $(addprefix srcs/, $(SRCSF)) \
				  $(addprefix srcs/Built_in/, $(BUILT_IN)) \
				  $(addprefix srcs/Parsing/, $(PARSING)) \
				  $(addprefix srcs/Redirect/, $(REDIRECT)) \
				  $(addprefix srcs/Exec_cmd/, $(EXEC_CMD)) \
				  $(addprefix srcs/Toolbox/, $(TOOLBOX))

OBJS			= $(SRCS:.c=.o)

CC				= gcc

RM				= rm -f

CFLAGS			= -g3 #-fsanitize=address #-Wall -Wextra -Werror

all:			$(NAME)

%.o: 			%.c	 $(HEADERS)
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