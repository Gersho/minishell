NAME			=	minishell

HEADERS			=	headers/minishell.h		\
					headers/shell_struct.h	\
				 	headers/built_in.h		\
				 	headers/exec_cmd.h		\
				 	headers/tools.h			\
				 	headers/env_list.h		\
				 	headers/redirect.h 		\
				 	headers/signals.h		\
				 	headers/libft.h			\

BUILT_IN		=	echo.c			\
				 	env.c			\
				 	pwd.c			\
				 	cd.c			\
				 	export.c		\
				 	print_export.c	\
				 	unset.c			\
				 	exit.c			\

EXEC_CMD		= parse_cmd.c		\
                  cmd_launcher.c	\
                  exec_built_in.c	\
                  exec_cmd_fork.c	\
                  get_cmd_path.c	\
                  split_env_path.c

PARSING			= debug.c				\
				  dollars.c				\
				  exits.c				\
				  parse_tools.c			\
				  parse_input.c			\
				  s_cmd.c				\
  				  tools.c				\
				  param_utils.c			\
				  s_vars.c				\
				  s_quotes.c			\
				  str_manipulation.c	\
				  red_tools.c

SRCSF			= main.c		\
				  minishell.c	\
				  set_prompt.c	\

TOOLBOX			= close_tools.c		\
				  env_tools.c		\
				  	replace_std.c	\
				  	utils.c			\

REDIRECT		= here_doc.c 			\
                  redirect_handler.c	\
                  redirect_tools.c

ENV_LIST		= env_unlink.c 	\
				  s_env.c 		\
				  env_dup.c 	\
				  env_add_back.c

SIGNALS			=	sig_child.c \
					sig_pap.c 	\

SRCS			=	$(SRCSF)							\
				 	$(addprefix Built_in/, $(BUILT_IN)) \
				 	$(addprefix Parsing/, $(PARSING)) 	\
				 	$(addprefix Redirect/, $(REDIRECT)) \
				 	$(addprefix Exec_cmd/, $(EXEC_CMD)) \
				 	$(addprefix Toolbox/, $(TOOLBOX)) 	\
				 	$(addprefix Env_list/, $(ENV_LIST)) \
				 	$(addprefix Signals/, $(SIGNALS)) 	\

OBJS			=	$(addprefix .objs/, $(SRCS:.c=.o))

CC				= gcc

RM				= rm -rf

CFLAGS			= -g3 #-fsanitize=address #-Wall -Wextra -Werror

all:			libs $(NAME)

.objs/%.o: 		srcs/%.c $(HEADERS)
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS) libft/libft.a
				$(CC) $(CFLAGS) -L /Users/$$USER/.brew/opt/readline/lib -I /Users/$$USER/.brew/opt/readline/include -o $(NAME) $(OBJS) libft/libft.a -lreadline

libs:
				make -C libft/

clean:
				make clean -C libft/
				$(RM) .objs/

fclean:			clean
				make fclean -C libft/
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all libs clean fclean re
