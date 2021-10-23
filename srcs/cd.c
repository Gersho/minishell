//
// Created by Stellar on 21/10/2021.
//

#include "../headers/minishell.h"

void cd(char **param, t_env *env_l)
{
	int		i;
	char	buf[PATH_MAX];
	t_env	*env;


	i = 0;
	env = env_seeker(env_l, "HOME");
	while (param[i])
		i++;
	if (param[1] == NULL || *param[1] == '~')
		chdir(env->value);
	else if (i > 4)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (i == 3)
		dprintf(2, "cd: string not in pwd: %s\n", param[1]);
	else
	{
		env_ch_value(env_seeker(env_l, "OLDPWD"), getcwd(buf, PATH_MAX));
		if (chdir(param[1]) == -1)
		{
			perror("cd");
			return ;
		}
		env_ch_value(env_seeker(env_l, "PWD"), getcwd(buf, PATH_MAX));
	}
}