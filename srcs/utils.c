//
// Created by Johan Chevet on 10/14/21.
//

#include "../headers/minishell.h"

int skip_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void 	print_error_prompt(char *str)
{
	ft_printf_fd(2, "%s: ", PROMPTERR);
	perror(str);
}

char *str_in_lower_case(char *s)
{
	int		i;
	char	*str;
	
	i = 0;
	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		str[i] = ft_tolower((int)str[i]);
		i++;
	}
	return (str);
}