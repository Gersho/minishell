//
// Created by Johan Chevet on 10/12/21.
//

#include "../headers/minishell.h"

int is_built_in(char *param, int *cmd)
{
	char	*name;
	int		cmdd;

	if (cmd == NULL)
		cmd = &cmdd;
	*cmd = -1;
	name = str_in_lower_case(param);
	if (name == NULL)
		return (0);
	if (ft_strcmp("echo", name) == 0)
		*cmd = ECHO;
	else if (ft_strcmp("pwd", name) == 0)
		*cmd = PWD;
	else if (ft_strcmp("cd", name) == 0)
		*cmd = CD;
	else if (ft_strcmp("env", name) == 0)
		*cmd = ENV;
	else if (ft_strcmp("export", name) == 0)
		*cmd = EXPORT;
	else if (ft_strcmp("unset", name) == 0)
		*cmd = UNSET;
	else if (ft_strcmp("exit", name) == 0)
		*cmd = EXIT;
	free(name);
	if (*cmd != -1)
		return (1);
	return (0);
}


int create_child_to_exec_cmd(t_shell *shell, int *pid)
{
	char	**env_t;
	char	**path_tab;

	*pid = fork();
	if (*pid == 0)
	{
		if (shell->cmd->next)
			close_unused_fd(shell);
		if (*shell->cmd->param)
		{
			if (check_built_in(shell, 1))
				exit(EXIT_SUCCESS);//TODO peut pas que sucess
			path_tab = split_env_path(shell->env);
			shell->ret = get_cmd_path(shell, path_tab);
			env_t = get_env_tab(shell->env);
			if (shell->ret > 0)
			{
				free_cmd_list(shell->cmd);
				exit(shell->ret);
			}
			execve(shell->cmd->path, shell->cmd->param, env_t);
			perror(*shell->cmd->param);
			exit(EXIT_FAILURE);
		}
		else
			exit(EXIT_SUCCESS);
	}
	else if (*pid == -1)
		perror("fork");
	return (-1);
}

int check_built_in(t_shell *shell, int in_fork)
{
	int command;

	if (*shell->cmd->param)
	{
		if (is_built_in(*shell->cmd->param, &command))
		{
			if (command == ECHO)
				shell->ret = echo(shell->cmd->param);
			else if (command == PWD)
				shell->ret = pwd(shell->cmd->param, shell->env);
			else if (command == CD)
				shell->ret = cd(shell->cmd->param, shell->env);
			else if (command == ENV)
				shell->ret = env(shell->env);
			else if (command == EXPORT)
				shell->ret = export(shell->cmd->param, &shell->env);
			else if (command == UNSET)
				shell->ret = unset(shell->cmd->param, &shell->env);
			else if (command == EXIT)
				exit_shell(shell, in_fork);
			return (1);
		}
	}
	return (0);
}

int 	launch_all_commands(t_shell *shell, int *status)
{
	int	pid;
	int i;

	i = 0;
	while (shell->cmd)
	{
		dup2_close(shell->cmd->in, 0);
		dup2_close(shell->cmd->out, 1);
		if (i == 0 && !shell->cmd->next && is_built_in(*shell->cmd->param, NULL))
		{
			check_built_in(shell, 0);
			*status = -1;
		}
		else
			create_child_to_exec_cmd(shell, &pid);
		if (!shell->cmd->next)
		{
			dup2(shell->std_in, 0);
			dup2(shell->std_out, 1);
		}
		shell->cmd = shell->cmd->next;
		i++;
	}
	return pid;
}

int exec_cmd(t_shell *shell)
{
	int pid;
	int status;
	t_cmd *save = shell->cmd;

	shell->error = 0;
	status = 0;
	redirect_handler(shell);
	if (!shell->error)
		pid = launch_all_commands(shell, &status);
	else
	{
		close_all_fds(shell);
		shell->ret = EXIT_FAILURE;
	}
	if (status != -1)
	{
		waitpid(pid, &status, 0);
		shell->ret = WEXITSTATUS(status);
		while (wait(NULL) != -1)
			;
	}
	free_cmd_list(save);
	return (1);
}
