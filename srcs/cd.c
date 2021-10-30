//
// Created by Stellar on 21/10/2021.
//

#include "../headers/minishell.h"

int cd(char **param, t_env *env_l)
{
	char	buf[PATH_MAX];
	t_env	*env;

	
	if (param[1] == NULL || *param[1] == '~')
	{
		if (!env_seeker(&env_l, "HOME"))
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		env = env_l;
		if (env_seeker(&env_l, "OLDPWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		env_l = env;
		chdir(env_l->value);
		if (env_seeker(&env_l, "PWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		return (EXIT_SUCCESS);
	}
	else
	{
		env = env_l;
		if (env_seeker(&env_l, "OLDPWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		if (chdir(param[1]) == -1)
		{
			ft_printf_fd(2, "%s: cd: %s: %s\n", PROMPTERR, param[1], strerror(errno));
			return (EXIT_FAILURE);
		}
		env_l = env;
		if (env_seeker(&env_l, "PWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		return (EXIT_SUCCESS);
	}
}