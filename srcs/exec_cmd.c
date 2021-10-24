//
// Created by Johan Chevet on 10/12/21.
//

#include "../headers/minishell.h"

int is_build_in(char *param, int *cmd)
{
	char *name;
	
	*cmd = -1;;
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

	*pid = fork();
	if (*pid == 0)
	{
		path_tab = split_env_path(env_l);
//		dprintf(2, "cmd path =%s\n", cmd->path);
		get_cmd_path(cmd, path_tab);
		env_t = get_env_tab(env_l);
//		dprintf(2, "cmd path =%s\n", cmd->path);
		execve(cmd->path, cmd->param, env_t);
		perror(*cmd->param);
		dprintf(2, "cmd path =%s\n", cmd->path);
		exit(EXIT_FAILURE);
	}
	else if (*pid == -1)
		perror("fork");
	return (-1);
}

void init_fd(t_fds *fd)
{
	fd->std_in = dup(0);
	fd->std_out = dup(1);
	fd->prev_pipe_in = 0;
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

void set_pipe(t_cmd *cmd, t_fds *fds, int cmd_index)
{
	cmd->fd = fds;
	if (pipe(cmd->fd->pipe) == -1)
		perror("pipe");
//	dprintf (2, "pipe[0] = %d | pipe[1] = %d\n", cmd->fd->pipe[0], cmd->fd->pipe[1]);
	if (cmd_index > 0) //if not first cmd, replace current input by previous pipe input
	{
//		dprintf (2, "PREV pipe = %d\n", cmd->fd->prev_pipe_in);
//		dup2_close(cmd->fd->prev_pipe_in, 0);
	}
	if (cmd->next) //if there is a next command replace current output by pipe output
		dup2_close(cmd->fd->pipe[1], 1);
//	else if (cmd_index > 0 && !cmd->next) //if this is last cmd replace current output by stdout
//		dup2(cmd->fd->std_out, 1);
}

int check_built_in(char **param, t_env **env_l)
{
	int cmd;
	
	if (is_build_in(*param, &cmd))
	{
		if (cmd == ECHO)
			echo(param);
		else if (cmd == PWD)
			pwd(param, *env_l);
		else if (cmd == CD)
			cd(param, *env_l);
		else if (cmd == ENV)
			env(*env_l);
		else if (cmd == EXPORT)
			export(param, env_l);
		else if (cmd == UNSET)
			unset(param, env_l);
		else if (cmd == EXIT)
			exit_shell(param, *env_l);
		return (1);
	}
	return (0);
}

int exec_cmd(t_cmd *cmd, t_env **env_l)
{
	char **path_tab;
	int pid;
	int cmd_index;
	t_fds fds;
//	t_env *env_l = *env;
//	*env_l = *env_l->next;
	//TODO check if cmd is absolute path
	//TODO cat | heredoc, heredoc first
	//TODO fix pipe again
//	update_env_tab(env_t);
	cmd_index = 0;
	init_fd(&fds);
//	printf ("stdin = %d | stdout = %d\n", fds.std_in, fds.std_out);
//	env_l = env_l->next;
//	printf("in func :%s\n", (*env_l)->name);
//	return 1;
	while (cmd != NULL)
	{
		set_pipe(cmd, &fds, cmd_index);
		if(!redirect_handler(cmd->red, cmd))
		{
			dup2_close(cmd->fd->std_out, 1);
			return 1;
		}
		if (!check_built_in(cmd->param, env_l))
			create_child_to_exec_cmd(cmd, *env_l, &pid);//if return -1 free exit
		if (cmd->next)
			dup2_close(cmd->fd->pipe[0], 0);
		else
			dup2(cmd->fd->std_in, 0);
//			cmd->fd->prev_pipe_in = dup(cmd->fd->pipe[0]);//dup2_close(cmd->fd->pipe[0], 0)?
		dup2(cmd->fd->std_out, 1);
		cmd = cmd->next;
		cmd_index++;
	}
	waitpid(pid, NULL, 0);
	if (cmd_index > 1)
		while (wait(NULL) != -1)
			;
	return (1);
}

//TODO handle "echo blalba >" || "echo blabla ><"
//TODO "e""c""h""o" && close bad file descriptor probleme with multi here doc
