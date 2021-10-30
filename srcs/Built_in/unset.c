//
// Created by Johan Chevet on 10/23/21.
//

#include "../../headers/minishell.h"
//unset HOSTTYPE LANG LESS LOGNAME ZSH TERM SHLVL PWD PATH NAME MAIL LS_COLORS LSCOLORS USER OLDPWD PAGER SHELL WSLENV WSL_DISTRONAME WSL_INTEROP HOME PWD OLDPWD WSL_DISTRO_NAME
//unset Apple_PubSub_Socket_Render COMMAND_MODE DISPLAY HOME HOMEBREW_CACHE HOMEBREW_TEMP LC_CTYPE LESS LOGIN_SHELL LOGNAME LSCOLORS MAIL OLDPWD PAGER PATH PWD SECURITYSESSIONID SHELL SHLVL SSH_AUTH_SOCK TERM TMPDIR USER XPC_FLAGS XPC_SERVICE_NAME ZSH _ __CF_USER_TEXT_ENCODING __INTELLIJ_COMMAND_HISTFILE__ TERMINAL_EMULATOR
int 	unset(char **param, t_env **env_l)
{
	t_env *tmp;
	int		i;

	i = 0;
	if (param[1] == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (EXIT_FAILURE);
	}

	while (param[++i])
	{
		tmp = *env_l;
		if (env_seeker(&tmp, param[i]))
		{
			*env_l = env_unlink(*env_l, tmp->name);
			if (*env_l == NULL)
				break ;
		}
	}
	return (EXIT_SUCCESS);
}