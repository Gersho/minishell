/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:40:29 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/27 11:32:24 by jchevet          ###   ########lyon.fr   */
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
	if (!ft_isdigit((int)str[i]))
		*err = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	i += skip_spaces(str + i);
	if (str[i])
		*err = 1;
	return (ret * (long long)is_neg);
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

static int	exit_value_cmp(long long nb, char *exit_value)
{
	char	*str;
	int		i;
	int		start;

	str = lltoa(nb);
	if (!str)
		return (1);
	i = skip_spaces(exit_value);
	start = i;
	while (exit_value[i] >= '0' && exit_value[i] <= '9')
		i++;
	i = ft_strncmp(exit_value, &str[start], i - start);
	free(str);
	return (i);
}

static int	get_return_value(t_shell *shell)
{
	long long		exit_status;
	int				err;

	if (shell->cmd->param[1])
	{
		exit_status = ft_atoll_exit(shell->cmd->param[1], &err);
		if (err || exit_value_cmp(exit_status, shell->cmd->param[1]))
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
			shell->ret = (int)exit_status;
	}
	return (1);
}

void	exit_shell(t_shell *shell, int in_fork)
{
	if (!in_fork)
		ft_printf_fd(2, "exit\n");
	if (shell->cmd)
	{
		if (!get_return_value(shell))
			return ;
	}
	free_all(shell, 0, NULL);
	exit((unsigned char)shell->ret);
}
