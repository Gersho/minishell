/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:34 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:40:36 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_plus_equal(char *param, char *name, t_env *env, int i)
{
	char	*tmp;

	if (param[i] == '+' && param[i + 1] == '=')
	{
		if (!env_seeker(&env, name))
			env_add_back(&env, new_env(name, \
			ft_substr(param, i + 2, ft_strlen(param))));
		else
		{
			tmp = env->value;
			env->value = ft_strjoin(env->value, param + i + 2);
			free(tmp);
		}
		return (1);
	}
	return (0);
}

static int	is_equal(char *param, char *name, t_env *env, int i)
{
	if (param[i] == '=')
	{
		if (!env_seeker(&env, name))
			env_add_back(&env, new_env(name, \
			ft_substr(param, i + 1, ft_strlen(param))));
		else
		{
			free(env->value);
			env->value = ft_substr(param, i + 1, ft_strlen(param));
		}
		return (1);
	}
	return (0);
}

static int	check_sign(char *param, t_env *env, int i)
{
	char	*name;

	if (param[i] == '+' || param[i] == '=')
	{
		name = ft_substr(param, 0, i);
		if (is_plus_equal(param, name, env, i))
			return (1);
		if (is_equal(param, name, env, i))
			return (1);
	}
	return (0);
}

void	parse_export(char *param, t_env **env)
{
	t_env	*envptr;
	int		i;

	i = 0;
	envptr = *env;
	while (param[i])
	{
		if (check_sign(param, *env, i))
			break ;
		i++;
		if (param[i] == '\0')
		{
			if (!env_seeker(&envptr, param))
				env_add_back(env, new_env(ft_strdup(param), NULL));
		}
	}
}

int	export(char **param, t_env **env)
{
	int	j;
	int	ret;

	ret = 0;
	j = 0;
	if (param[1] == NULL)
		return (print_env_export(*env));
	while (param[++j])
	{
		if (!ft_isalpha((int)param[j][0]) && param[j][0] != '_')
		{
			ft_printf_fd(2, "%s: export: '%s': not an identifier\n", \
			PROMPTERR, param[j]);
			ret = 1;
			continue ;
		}
		parse_export(param[j], env);
	}
	return (ret);
}
