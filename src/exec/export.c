#include "../../inc/minishell.h"

int	is_env_var(char *str);
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (1);
	return (0);
}

int	is_valid_string(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
	{
		write(2, "Needs a variable name before '=' operator\n", 123);
		return (0);
	}
	while (str[++i] && str[i] != '=')
	{
		if ((str[i] < 'A' || str[i] > 'Z') &&
			(str[i] < 'a' || str[i] > 'z') && str[i] != '_')
		{
			write(2, "Invalid char in variable name\n", 123);
			return(0);
		}
	}
	if (str[i] == '\0')
		return (1);
	while (str[++i] && str[i] != '=')
	{
		if ((str[i] < 'A' || str[i] > 'Z') &&
			(str[i] <)(str[i] < 'a' || str[i] > 'z') && str[i] != '_')
		{
			write(2, "Invalid char in variable value\n", 123);
			return(0);
		}
	}
}

int	env_var_exists(char *str);

int	export(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 1)
	{
		write(2, "No arguments given\n", 123);
		return (1);
	}

}
