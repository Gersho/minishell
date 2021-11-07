//
// Created by Stellar on 24/10/2021.
//

#include "../../headers/minishell.h"

static int		ft_atoi_exit(char *str, int *err)
{
	int i;
	int	ret;
	int is_neg;

	*err = 0;
	is_neg = 1;
	ret = 0;
	i = skip_spaces(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i])
		*err = 1;
	ret *= is_neg;
	return (ret);
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

static void get_return_value(t_shell *shell)
{
	unsigned char	exit_status;
	int 			err;

	exit_status = (unsigned char)ft_atoi_exit(shell->cmd->param[1], &err);
	if (err)
	{
		ft_printf_fd(2, "%s: exit: %s: numeric argument required\n", \
				PROMPTERR, shell->cmd->param[1]);
		shell->ret = 255;
	}
	else if (more_than_one_param(shell->cmd->param))
		shell->ret = 1;
	else
		shell->ret = (int)exit_status;
}

void	exit_shell(t_shell *shell, int in_fork)
{
	if (shell->cmd)
		get_return_value(shell);
	if (!in_fork)
	{

		ft_printf_fd(2, "exit %d\n", shell->ret);
		close_perror(shell->std_out);
		close_perror(shell->std_in);
	}
	tcsetattr(0, TCSANOW, &shell->term);
	free_env_list(shell->env);
	free_cmd_list(shell->cmd);
	exit(shell->ret);
}
