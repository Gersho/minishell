//
// Created by Johan Chevet on 11/4/21.
//

#include "../../headers/minishell.h"

int	is_built_in(char *param)
{
	char 		*name;
	t_cmd_name	cmd;

	cmd = NOT_BUILT_IN_M;
	name = str_in_lower_case(param);
	if (name == NULL)
		return (0);
	if (ft_strcmp("echo", name) == 0)
		cmd = ECHO_M;
	else if (ft_strcmp("pwd", name) == 0)
		cmd = PWD_M;
	else if (ft_strcmp("cd", name) == 0)
		cmd = CD_M;
	else if (ft_strcmp("env", name) == 0)
		cmd = ENV_M;
	else if (ft_strcmp("export", param) == 0)
		cmd = EXPORT_M;
	else if (ft_strcmp("unset", param) == 0)
		cmd = UNSET_M;
	else if (ft_strcmp("exit", param) == 0)
		cmd = EXIT_M;
	free(name);
	return (cmd);
}

int	exec_built_in(t_shell *shell, int in_fork)
{
	int	command;
	if (*shell->cmd->param)
	{
		command = is_built_in(*shell->cmd->param);
		if (!in_fork)
		{

			shell->std_in = dup(0);
			shell->std_out = dup(1);
			dup2_close(shell->cmd->in, 0);
			dup2_close(shell->cmd->out, 1);
		}
		if (command != NOT_BUILT_IN_M)
		{
			if (command == ECHO_M)
				shell->ret = echo(shell->cmd->param);
			else if (command == PWD_M)
				shell->ret = pwd(shell->cmd->param);
			else if (command == CD_M)
				shell->ret = cd(shell->cmd->param, shell->env);
			else if (command == ENV_M)
				shell->ret = env(shell->env);
			else if (command == EXPORT_M)
				shell->ret = export(shell->cmd->param, &shell->env);
			else if (command == UNSET_M)
				shell->ret = unset(shell->cmd->param, &shell->env);
			else
				exit_shell(shell, in_fork);
			if (!in_fork)
			{
				dup2_close(shell->std_in, 0);
				dup2_close(shell->std_out, 1);
			}
			return (1);
		}
	}
	return (0);
}
