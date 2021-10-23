//
// Created by Stellar on 21/10/2021.
//

#include "../headers/minishell.h"

void cd(char **param, t_env *env_l)
{
	int		i;
	char	buf[PATH_MAX];
//	t_env	*env;


	i = 0;
	env_seeker(&env_l, "HOME");
	while (param[i])
		i++;
	if (param[1] == NULL || *param[1] == '~')
	{
		if (env_seeker(&env_l, "OLDPWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		chdir(env_l->value);
		if (env_seeker(&env_l, "PWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
	}
	else if (i > 4)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (i == 3)
		dprintf(2, "cd: string not in pwd: %s\n", param[1]);
	else
	{
		if (env_seeker(&env_l, "OLDPWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		if (chdir(param[1]) == -1)
		{
			perror("cd");
			return ;
		}
		if (env_seeker(&env_l, "PWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
	}
}