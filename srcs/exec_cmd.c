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
		return (-1);
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

void 	close_unused_fd(t_shell *shell)
{
	t_cmd *ptr;

	ptr = shell->cmd->next;
	while (ptr)
	{
		close_perror(ptr->in);
		close_perror(ptr->out);
		ptr = ptr->next;
	}
	close_perror(shell->std_out);
	close_perror(shell->std_in);
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
		if (check_built_in(shell))
			exit(EXIT_SUCCESS);//TODO peut pas que sucess
		path_tab = split_env_path(shell->env);
		get_cmd_path(shell->cmd, path_tab);
		env_t = get_env_tab(shell->env);
		execve(shell->cmd->path, shell->cmd->param, env_t);
		perror(*shell->cmd->param);
		exit(EXIT_FAILURE);
	}
	else if (*pid == -1)
		perror("fork");
	return (-1);
}

void close_fds(int nb, ...)
{
	va_list	fd_list;
	int		fd;
	int		i;
	
	i = 0;
	va_start(fd_list, nb);
	while (i < nb)
	{
		fd = (int) va_arg(fd_list, int);
		close_perror(fd);
		i++;
	}
	va_end(fd_list);
}


int check_built_in(t_shell *shell)
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
				exit_shell(shell->cmd, shell->env);
			return (1);
		}
	}
	return (0);
}

int exec_cmd(t_shell *shell)
{
	int pid;
	int cmd_index;
	int status;
	t_cmd *save = shell->cmd;
	//TODO cat | <<  yo random segf && echo yo | exit
	//todo segf printf("cmd=%s\n", cmd->param[0]); in term
	cmd_index = 0;
	shell->error = 0;
	status = 0;
	redirect_handler(shell);
	if (!shell->error)
	{
		while (shell->cmd)
		{
			dup2_close(shell->cmd->in, 0);
			dup2_close(shell->cmd->out, 1);
			if (cmd_index == 0 && !shell->cmd->next && is_built_in(*shell->cmd->param, NULL))
			{
				check_built_in(shell);
				status = -1;
			}
			else
			{
				create_child_to_exec_cmd(shell, &pid);
			}
			if (!shell->cmd->next)
			{
				dup2(shell->std_in, 0);
				dup2(shell->std_out, 1);
			}
			shell->cmd = shell->cmd->next;
			cmd_index++;
		}
	}
	else
	{
		//close all fds
		shell->ret = EXIT_FAILURE;
	}
	if (status != -1)
	{
		waitpid(pid, &status, 0);
		shell->ret = WEXITSTATUS(status);
		while (wait(NULL) != -1);
			;
	}
	free_cmd_list(save);
	return (1);
}

//TODO handle "echo blalba >" || "echo blabla ><"
//TODO "e""c""h""o" && close bad file descriptor probleme with multi here doc
