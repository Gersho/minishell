/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:29 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/09 08:40:29 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static long long	ft_atoll_exit(char *str, int *err)
{
	int			i;
	long long	ret;
	int			is_neg;

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
	i += skip_spaces(str + i);
	if (str[i])
		*err = 1;
	ret *= (long long)is_neg;
	printf("ret=%lld\n", ret);
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

static int	get_return_value(t_shell *shell)
{
	unsigned char	exit_status;
	int				err;

	if (shell->cmd->param[1])
	{
		exit_status = (unsigned char)ft_atoll_exit(shell->cmd->param[1], &err);
		printf("exit status=%d\n", (int)exit_status);
		if (err)
		{
			ft_printf_fd(2, "%s: exit: %s: numeric argument required\n", \
			PROMPTERR, shell->cmd->param[1]);
			shell->ret = 255;
		}
		else if (more_than_one_param(shell->cmd->param))
		{
			shell->ret = 1;
			return (0);
		}
		else
			shell->ret = (int) exit_status;
	}
	return (1);
}

void	exit_shell(t_shell *shell, int in_fork)
{
	if (shell->cmd)
	{
		if (!get_return_value(shell))
			return ;
	}
	if (!in_fork)
	{
		if (shell->cmd)
		{
			close_perror(shell->std_out);
			close_perror(shell->std_in);
		}
		ft_printf_fd(2, "exit\n");
	}
	tcsetattr(0, TCSANOW, &shell->term);
	free_env_list(shell->env);
	free_cmd_list(shell->cmd);
	exit(shell->ret);
}
