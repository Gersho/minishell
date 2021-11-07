NAME			= minishell

HEADERS			= headers/minishell.h \
				  headers/built_in.h \
				  headers/exec_cmd.h \
				  headers/tools.h \
				  headers/env_list.h \
				  headers/redirect.h \
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
				  s_quotes.c

SRCSF			= main.c \
				  minishell.c \
				  set_prompt.c

TOOLBOX			= close_tools.c \
				  env_tools.c \
				  utils.c

REDIRECT		= here_doc.c \
                  redirect_handler.c \
                  redirect_tools.c

ENV_LIST		= env_unlink.c \
				  s_env.c \
				  env_dup.c \
				  env_add_back.c

SRCSFO			= 	$(BUILT_IN) \
					$(SRCSF) \
					$(PARSING) \
					$(REDIRECT) \
					$(EXEC_CMD) \
					$(TOOLBOX) \
					$(ENV_LIST)

SRCS			= $(SRCSF) \
				  $(addprefix Built_in/, $(BUILT_IN)) \
				  $(addprefix Parsing/, $(PARSING)) \
				  $(addprefix Redirect/, $(REDIRECT)) \
				  $(addprefix Exec_cmd/, $(EXEC_CMD)) \
				  $(addprefix Toolbox/, $(TOOLBOX)) \
				  $(addprefix Env_list/, $(ENV_LIST))

OBJDIR			= .objs/ \
				  .objs/Built_in/ \
				  .objs/Parsing/ \
				  .objs/Redirect/ \
				  .objs/Exec_cmd/ \
				  .objs/Toolbox/ \
				  .objs/Env_list/

OBJS			=  $(SRCS:.c=.o)

OBJSLOCATION	=	 $(addprefix .objs/, $(OBJS))

CC				= gcc

RM				= rm -rf

CFLAGS			= -g3 #-fsanitize=address #-Wall -Wextra -Werror

all:			$(NAME)

.objs/%.o: 		srcs/%.c	 $(HEADERS)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		create_dir $(OBJSLOCATION)
				make -C libft/
				$(CC) $(CFLAGS) \
				-L /Users/$$USER/.brew/opt/readline/lib \
				-I/Users/$$USER/.brew/opt/readline/include \
				-o $(NAME) $(OBJSLOCATION) libft/libft.a -lreadline


create_dir:
				mkdir -p $(OBJDIR)

clean:
				make clean -C libft/
				$(RM) $(OBJS)
				$(RM) $(OBJDIR)

fclean:			clean
				make fclean -C libft/
				$(RM) $(NAME)
				make fclean -C libft/

re:				fclean all

.PHONY:			re fclean clean all