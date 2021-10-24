//
// Created by Stellar on 22/10/2021.
//

#include "../headers/minishell.h"

char	*ft_mega_str_join(int nb, ...)
{
	char	*mega_str;
	char 	*str;
	char 	*tmp;
	int i;

	i = 1;
	va_list	args;
	va_start(args, nb);
	mega_str = (char*)va_arg(args, char *);
	while (i < nb)
	{
		str = (char*)va_arg(args, char *);
		tmp = mega_str;
		mega_str = ft_strjoin(mega_str, str);
		if (!mega_str)
		{
			va_end(args);
			return (NULL);
		}
		if (i > 1)
			free(tmp);
		i++;
	}
	va_end(args);
	return (mega_str);
}

//❌✖➜🌻
char 	*set_prompt(t_env *env)
{
	char	*def;
	char	*prompt;
	t_env   *env_found;
	char 	*curr_dir;
	char 	buf[PATH_MAX];

	def = "bash$: ";
	getcwd(buf, PATH_MAX);
	curr_dir = ft_strrchr(buf, (int)'/') + 1;
	prompt = ft_mega_str_join(11,
								KGRN, "➜  ",\
							  	KCYN, curr_dir,	\
							  	KBLU, " (", \
							  	KRED, getenv("USER"), \
						   		KBLU, "): ", \
						   		KNRM);
	return (prompt);
}
