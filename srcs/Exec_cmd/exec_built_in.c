//
// Created by Johan Chevet on 11/4/21.
//

#include "../../headers/minishell.h"

int	is_built_in(char *param)
{
	char 		*name;
	t_cmd_name	cmd;

	cmd = NOT_BUILT_IN;
	name = str_in_lower_case(param);
	if (name == NULL)
		return (0);
	if (ft_strcmp("echo", name) == 0)
		cmd = ECHO;
	else if (ft_strcmp("pwd", name) == 0)
		cmd = PWD;
	else if (ft_strcmp("cd", name) == 0)
		cmd = CD;
	else if (ft_strcmp("env", name) == 0)
		cmd = ENV;
	else if (ft_strcmp("export", param) == 0)
		cmd = EXPORT;
	else if (ft_strcmp("unset", param) == 0)
		cmd = UNSET;
	else if (ft_strcmp("exit", param) == 0)
		cmd = EXIT;
	free(name);
	return (cmd);
}

int	exec_built_in(t_shell *shell, int in_fork)
{
	int	command;

	if (*shell->cmd->param)
	{
		command = is_built_in(*shell->cmd->param);
		if (command != NOT_BUILT_IN)
		{
			if (command == ECHO)
				shell->ret = echo(shell->cmd->param);
			else if (command == PWD)
				shell->ret = pwd(shell->cmd->param);
			else if (command == CD)
				shell->ret = cd(shell->cmd->param, shell->env);
			else if (command == ENV)
				shell->ret = env(shell->env);
			else if (command == EXPORT)
				shell->ret = export(shell->cmd->param, &shell->env);
			else if (command == UNSET)
				shell->ret = unset(shell->cmd->param, &shell->env);
			else
				exit_shell(shell, in_fork);
			return (1);
		}
	}
	return (0);
}
