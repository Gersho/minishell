//
// Created by Johan Chevet on 10/12/21.
//

#include "../headers/minishell.h"

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
	std_in = dup(0);
	int	prev_pipe_r;
	while (cmd != NULL)
	{
		if (pipe(pipe_fd) == -1)
			perror("pipe");
		if (i > 0)
			dup2_close(prev_pipe_r, 0);
		if (cmd->next)//if there is a pipe
			dup2(pipe_fd[1], 1);
		else
			dup2(std_out, 1);
		pid = fork();
		if (pid == 0)
		{
			if (cmd->red)
				redirect_handler(cmd->red);
			get_cmd_path(cmd, path_tab);
			execve(cmd->path, cmd->param, env);
			perror("execve");
		}
		else if (pid == -1)
			return (-1);//perror fork
		if (cmd->next)
			prev_pipe_r = dup(pipe_fd[0]);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		cmd = cmd->next;
		i++;
	}
	if (i > 1)
		close(prev_pipe_r);
	return (1);
}

//int main(int ac, char **av, char **env)
//{
//	t_cmd *cmd;
//	t_cmd *new;
//	//first cmd
//	cmd = ft_cmd_init();
//	cmd->param = ft_split("ls -la", ' ');
//	//second cmd
//	cmd->next = ft_cmd_init();
//	cmd->next->param = ft_split("grep test", ' ');
	
//	cmd->next->next = ft_cmd_init();
//	cmd->next->next->param = ft_split("wc -l", ' ');
//	cmd->next->next->red = ft_strdup("> test1.txt");


	exec_cmd(cmd, env);
	wait(NULL);
}