//
// Created by Stellar on 22/10/2021.
//

#include "../headers/minishell.h"

//❌✖➜🌻
char 	*set_prompt(t_shell *shell)
{
	char	*prompt;
	char 	*curr_dir;
	char 	buf[PATH_MAX];
	char	*status;
	
	//🌸🌻
	if (shell->ret == 0)
		status = "🌸 ";
	else
		status = "❌  ";
	
	getcwd(buf, PATH_MAX);
	curr_dir = ft_strrchr(buf, (int)'/') + 1;
	prompt = ft_mega_str_join(10,
								status,\
							  	KBLU, curr_dir,	\
							  	KMAG, " (", \
							  	KCYN, getenv("USER"), \
						   		KMAG, "): ", \
						   		KNRM);
	if (!prompt)
		prompt = ft_strdup("bash$ ");
	return (prompt);
}
