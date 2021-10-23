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
		if (i > 1)
			free(tmp);
		i++;
	}
	va_end(args);
	return (mega_str);
}

char 	*set_prompt(t_env *env)
{
	char	*prompt;
	t_env   *env_found;
	char 	*curr_dir;

	env_found = env_seeker(env, "PWD");
	if (env_found)
		curr_dir = ft_strrchr(env_found->value, (int)'/') + 1;
	prompt = ft_mega_str_join(11,
							  	KGRN, "🌻 ", KNRM, \
							  	KCYN, curr_dir,	" (", \
							  	KRED, getenv("USER"), \
						   		KCYN, "): ", \
						   		KNRM);
	return (prompt);
}
