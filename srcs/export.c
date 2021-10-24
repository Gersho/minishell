//
// Created by Johan Chevet on 10/22/21.
//

#include "../headers/minishell.h"

void 	print_env_export(t_env *env)
{
	t_env 	*save;
	t_env 	*cpy;

	save = env_dup(env);
	ft_printf_fd(2, "yoo\n");
	while (save)
	{
		cpy = save;
		while (cpy)
		{
			if (ft_strcmp(save->name, cpy->name) > 0)
				save = cpy;
			cpy = cpy->next;
		}
		printf("declare -x %s=\"%s\"\n", save->name, save->value);
		env_unlink(&save);
	}
}

static int	is_plus_equal(char *param, char *name, t_env *env, int i)
{
//	t_env	*env_l;
	char	*tmp;

	if (param[i] == '+' && param[i + 1] == '=')
	{
		env_seeker(&env, name);
		if (env == NULL)
			env_add_back(&env, new(name, ft_substr(param, i + 2, ft_strlen(param))));
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

static int is_equal(char *param, char *name, t_env *env, int i)
{
	t_env	*env_l;

	if (param[i] == '=')
	{
		env_seeker(&env, name);
		if (env == NULL)
			env_add_back(&env, new(name, ft_substr(param, i + 1, ft_strlen(param))));
		else
		{
			free(env->value);
			env->value = ft_substr(param, i + 1, ft_strlen(param));
		}
		return (1);
	}
	return (0);
}

static int check_equality(char *param, t_env *env, int i)
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
//TODO EXPORT unset IN MAJ == ERROR
void	export(char **param, t_env **env)
{
	int	i;
	int j;


	j = 0;
	if (param[1] == NULL)
		return (print_env_export(*env));
	while (param[++j])
	{
		i = 0;
		if (!ft_isalpha((int)param[j][0]) && param[j][0] != '_')
		{
			ft_printf_fd(2, "export: not an identifier: %s\n", param[j]);
			continue ;
		}
		while (param[j][i])
		{
			if (check_equality(param[j], *env, i))//TODO peut etre pas
				break ;
			i++;
			if (param[j][i] == '\0')
				env_add_back(env, new(ft_strdup(param[j]), ft_strdup("")));
		}
	}
}