//
// Created by Johan Chevet on 11/8/21.
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
