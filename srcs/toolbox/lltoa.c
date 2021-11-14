//
// Created by Johan Chevet on 11/14/21.
//

#include "../../headers/minishell.h"

static int	get_nb_len(long long nb)
{
	int len;

	len = 0;
	if (nb < 0)
		nb *= -1;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*lltoa(long long nb)
{
	char *str;


}