//
// Created by Johan Chevet on 10/23/21.
//

#include "../headers/minishell.h"
//TODO if path unset "ls command not found"
//unset HOSTTYPE LANG LESS LOGNAME ZSH TERM SHLVL PWD PATH NAME MAIL LS_COLORS LSCOLORS USER OLDPWD PAGER SHELL WSLENV WSL_DISTRONAME WSL_INTEROP HOME PWD OLDPWD WSL_DISTRO_NAME
void 	unset(char **param, t_env **env_l)
{
	t_env *tmp;
	int		i;

	i = 0;
	if (param[1] == NULL)
		return (ft_putstr_fd("unset: not enough arguments\n", 2));
	tmp = *env_l;
	while (param[++i])
	{
//		printf("param[i]=%s\n", param[i]);
		if (!env_seeker(&tmp, param[i])) {
			tmp = *env_l;
//			printf("env before unlink=%s\n", tmp->name);
			continue ;
		}
//		printf("env before unlink=%s\n", tmp->name);
		env_unlink(&tmp);
		if (!tmp)
			break ;
//		printf("after unlink=%s prev=%p next=%s\n",tmp->name, tmp->prev, tmp->next->name);
//		printf("after unlink=%s prev=%p next=%s\n", env_l->name, env_l->prev, env_l->next->name);
	}
	*env_l = tmp;
}