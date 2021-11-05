//
// Created by Johan Chevet on 10/22/21.
//

#include "../../headers/minishell.h"

int	print_env_export(t_env *env)
{
	t_env	*to_parse;
	t_env	*cpy;
	t_env	*save;

	cpy = env_dup(env);
	save = cpy;
	while (cpy)
	{
		to_parse = save;
		while (to_parse)
		{
			if (ft_strcmp(cpy->name, to_parse->name) > 0)
				save = to_parse;
			to_parse = to_parse->next;
		}
		if (save->value)
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", save->name, save->value);
		else
			ft_printf_fd(1, "declare -x %s\n", save->name, save->value);
		cpy = env_unlink(cpy, save->name);
		save = cpy;
	}
	return (0);
}

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
