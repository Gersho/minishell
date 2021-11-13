/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:05 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:40:05 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	update_oldpwd(t_env *env)
{
	t_env *env_ptr;

	env_ptr = env;
	if (env_seeker(&env_ptr, "PWD"))
	{
		if (env_seeker(&env, "OLDPWD"))
			env_ch_value(env, env_ptr->value);
	}
}

static int	go_home(t_env *env_l, char *buf)
{
	t_env	*env;

	env = env_l;
	if (!env_seeker(&env_l, "HOME"))
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	update_oldpwd(env);
	chdir(env_l->value);
	if (env_seeker(&env_l, "PWD"))
		env_ch_value(env_l, getcwd(buf, PATH_MAX));
	return (EXIT_SUCCESS);
}

int	cd(char **param, t_env *env_l)
{
	char	buf[PATH_MAX];
	t_env	*env;

	if (param[1] == NULL || *param[1] == '~')
		return (go_home(env_l, buf));
	else
	{
		env = env_l;
		update_oldpwd(env);
//		if (env_seeker(&env_l, "OLDPWD"))
//			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		if (chdir(param[1]) == -1)
		{
			ft_printf_fd(2, "%s: cd: %s: %s\n", \
			PROMPTERR, param[1], strerror(errno));
			return (EXIT_FAILURE);
		}
//		env_l = env;
		if (env_seeker(&env_l, "PWD"))
			env_ch_value(env_l, getcwd(buf, PATH_MAX));
		return (EXIT_SUCCESS);
	}
}
