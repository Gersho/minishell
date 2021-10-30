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

int create_child_to_exec_cmd(t_cmd *cmd, t_env *env_l, int *pid)
{
	char	**env_t;
	char	**path_tab;
	t_cmd  *ptr;
	*pid = fork();
	if (*pid == 0)
	{
		dup2_close(cmd->in, 0);
		dup2_close(cmd->out, 1);
		if (cmd->next)
		{
			ptr = cmd->next;
			while (ptr)
			{
				close_perror(ptr->in);
				close_perror(ptr->out);
				ptr = ptr->next;
			}
		}
		if (check_built_in(cmd, &env_l))
			exit(EXIT_SUCCESS);//TODO peut pas que sucess
		path_tab = split_env_path(env_l);
		get_cmd_path(cmd, path_tab);
		env_t = get_env_tab(env_l);
//		free_env_list(env_l);
		execve(cmd->path, cmd->param, env_t);
		perror(*cmd->param);
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


int check_built_in(t_cmd *cmd, t_env **env_l)
{
	int command;
	if (*cmd->param)
	{
		if (is_built_in(*cmd->param, &command))
		{
			if (command == ECHO)
				echo(cmd->param, cmd->out);
			else if (command == PWD)
				pwd(cmd->param, *env_l, cmd->out);
			else if (command == CD)
				cd(cmd->param, *env_l);
			else if (command == ENV)
				env(*env_l, cmd->out);
			else if (command == EXPORT)
				export(cmd->param, env_l, cmd->out);
			else if (command == UNSET)
				unset(cmd->param, env_l);
			else if (command == EXIT)
				exit_shell(cmd, *env_l);
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

	//TODO cat | <<  yo random segf && echo yo | exit
	cmd_index = 0;
	redirect_handler(shell->cmd);
	while (shell->cmd)
	{
		if (cmd_index == 0 && !shell->cmd->next && is_built_in(*shell->cmd->param, NULL))
			check_built_in(shell->cmd, &shell->env);
		else
			create_child_to_exec_cmd(shell->cmd, shell->env, &pid);
		close_perror(shell->cmd->in);
		close_perror(shell->cmd->out);
		shell->cmd = shell->cmd->next;
		cmd_index++;
	}
	waitpid(pid, &status, 0);
	shell->exit_status = WEXITSTATUS(status);
	while (wait(NULL) != -1)
		;
	free_cmd_list(shell->cmd);
	return (1);
}

//TODO handle "echo blalba >" || "echo blabla ><"
//TODO "e""c""h""o" && close bad file descriptor probleme with multi here doc
