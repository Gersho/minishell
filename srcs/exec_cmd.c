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

void check_built_in(char **param)
{
	if (ft_strcmp("echo", *param) == 0)//TODO tmp = *param ; tmp in lower case +strcoomp
		echo(param);
//	else if (ft_strcmp("pwd", cmd) == 0)
}

int exec_cmd(t_cmd *cmd, char **env)
{
	char **path_tab;
	int pid;
	int pipe_fd[2];
	int std_out;
	int std_in;
	int i = 0;
	path_tab = split_env_path(env);
	std_out = dup(1);
//	std_in = dup(0);
	int	prev_pipe_r;
	while (cmd != NULL)
	{
		if (pipe(pipe_fd) == -1)
			perror("pipe");
		if (i > 0)
			dup2_close(prev_pipe_r, 0);
		if (cmd->next)//if there is a pipe
			dup2_close(pipe_fd[1], 1);
		else
			dup2_close(std_out, 1);
		pid = fork();
		if (pid == 0)
		{
			if (cmd->red)
				redirect_handler(cmd->red);
			check_built_in(cmd->param);
			get_cmd_path(cmd, path_tab);
//			ft_putstr_nl_fd(cmd->path, std_out);
			execve(cmd->path, cmd->param, env);
			perror("execve");
			ft_putstr_nl_fd(cmd->path, std_out);
		}
		else if (pid == -1)
			return (-1);//perror fork
		if (cmd->next)
			prev_pipe_r = dup(pipe_fd[0]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
//		waitpid(pid, NULL, 0);
		cmd = cmd->next;
		i++;
	}
	if (i > 1)
		close(prev_pipe_r);
	waitpid(pid, NULL, 0);
	while (wait(NULL) == -1)
		;
	ft_putstr_nl_fd(" ouii", 1);
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_cmd *cmd;
	//first cmd

	cmd = ft_cmd_init();
//	cmd->param = ft_split("cat", ' ');
	cmd->red = ft_strdup("<< end");
	//second cmd
	cmd->next = ft_cmd_init();
//	cmd->next->param = ft_split("dfsafas", ' ');
	cmd->next->red = ft_strdup("<< ok");
	
//	cmd->next->next = ft_cmd_init();
//	cmd->next->next->param = ft_split("wc -l", ' ');
//	cmd->next->next->red = ft_strdup("> test1.txt");


	exec_cmd(cmd, env);
}