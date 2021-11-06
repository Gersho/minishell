//
// Created by Stellar on 24/10/2021.
//

#include "../../headers/minishell.h"

//TODO exit with args in unsigned char | avec quote

static int	str_is_all_num(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isalnum((int)str[i]))
			{
				ft_printf_fd(2, "$s: exit: %s: numeric argument required\n", \
				PROMPTERR, str);
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

static int	more_than_one_param(char **param)
{
	int	i;

	i = 0;
	while (param[i])
		i++;
	if (i > 2)
	{
		ft_printf_fd(2, "%s : exit: too many arguments\n", PROMPTERR);
		return (1);
	}
	return (0);
}

void	exit_shell(t_shell *shell, int in_fork)
{
	unsigned char	exit_status;


	if (shell->cmd && str_is_all_num(shell->cmd->param[1]))
	{
		if (!more_than_one_param(shell->cmd->param))
		{
			exit_status = (unsigned char) atoi(shell->cmd->param[1]);
			shell->ret = (int)exit_status;
		}
	}
	if (!in_fork)
	{

		ft_printf_fd(2, "exit\n");
		close_perror(shell->std_out);
		close_perror(shell->std_in);
	}
	tcsetattr(0, TCSANOW, &shell->term);
	free_env_list(shell->env);
	free_cmd_list(shell->cmd);
	exit(shell->ret);
}
