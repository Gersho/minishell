//
// Created by Johan Chevet on 10/12/21.
//

#include "../headers/minishell.h"

//int is_build_in(char *cmd)
//{
//	if (ft_strcmp("echo", cmd) == 0)
//		return (ECHO);
//	else if (ft_strcmp("pwd", cmd) == 0)
//		return (PWD);
//	else if (ft_strcmp("cd", cmd) == 0)
//		return (CD);
//	return (0);
//}//useless

int create_child_to_exec_cmd(t_cmd *cmd, char **path_tab, char **env, int *pid)
{
	*pid = fork();
	if (*pid == 0)
	{
		check_built_in(cmd->param);
		get_cmd_path(cmd, path_tab);
//		dprintf(2, "cmd par |%s|\n", *cmd->param);
		execve(cmd->path, cmd->param, env);
		perror("execve");
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
		dup2_close(cmd->fd->prev_pipe_in, 0);
	if (cmd->next) //if there is a next command replace current output by pipe output
		dup2_close(cmd->fd->pipe[1], 1);
	else if (cmd_index > 0 && !cmd->next) //if this is last cmd replace current output by stdout
		dup2_close(cmd->fd->std_out, 1);
}

void check_built_in(char **param)
{
	char *name;

	name = str_in_lower_case(*param);
	if (ft_strcmp("echo", name) == 0)//TODO tmp = *param ; tmp in lower case +strcoomp
	{
		free(name);
		echo(param);
	}
//	else if (ft_strcmp("pwd", cmd) == 0)
}

int exec_cmd(t_cmd *cmd, char **env)
{
	char **path_tab;
	int pid;
	int cmd_index;
	t_fds fds;
	
	//TODO cat | heredoc, heredoc first
	path_tab = split_env_path(env);//TODO liste chaine avec env
	cmd_index = 0;
	init_fd(&fds);
//	printf ("stdin = %d | stdout = %d\n", fds.std_in, fds.std_out);
	while (cmd != NULL)
	{
		set_pipe(cmd, &fds, cmd_index);
		if (cmd->red)
			redirect_handler(cmd->red, cmd);
		create_child_to_exec_cmd(cmd, path_tab, env, &pid);//if return -1 free exit
		if (cmd->next)
			cmd->fd->prev_pipe_in = dup(cmd->fd->pipe[0]);
		cmd = cmd->next;
		cmd_index++;
	}
	waitpid(pid, NULL, 0);
	if (cmd_index > 1)
		while (wait(NULL) == -1)
			;
	return (1);
}

//TODO handle "echo blalba >" || "echo blabla ><"
//TODO "e""c""h""o"
int main(int ac, char **av, char **env)
{
	t_cmd *cmd;
	//first cmd

	cmd = ft_cmd_init();
	cmd->param = ft_split("cat test.txt", ' ');
//	cmd->red = ft_strdup("<< oui");
//	second cmdgc

	cmd->next = ft_cmd_init();
	cmd->next->param = ft_split("cat", ' ');
//	cmd->next->red = ft_strdup("<< end");
	
//	cmd->next->next = ft_cmd_init();
//	cmd->next->next->param = ft_split("wc -l", ' ');
//	cmd->next->next->red = ft_strdup("> test1.txt");


	exec_cmd(cmd, env);
}