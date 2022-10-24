#include "../../inc/minishell.h"

int	export_error(char *str, int i, int error_type)
{
	if (error_type == 0)
	{
		write(2, "Needs a variable name before '=' operator\n", 123);
		return (0);
	}
	if (error_type == 1)
	{
		write(2, &str[i], 1);
		write(2, " : Invalid identifier before '='\n", 123);
		return (0);
	}
	return (0);
}

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

int	is_valid_identifier(char c)
{
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') &&
		(c < '0' || c > '9') && str[0] != '_')
		return (0);
	return (1);
}

int	is_valid_string(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
		return (export_error(str, 0, 0));
	if ((str[0] < 'A' || str[0] > 'Z') &&
		(str[0] < 'a' || str[i] > 'z') && str[0] != '_')
		return (export_error(str, 0, 1));
	while (str[++i] && str[i] != '=')
	{
		if (!is_valid_identifier(str[i]))
			return (export_error(str, i, 1));
	}
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	env_var_exists(char *str, char **envpc);
{
	int	i;

	i = 0;
	if (!str || !envpc)
		return (0);
	while (envpc[i] != NULL)
	{
		if (strcmp(str, envpc[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	export(int ac, char **av, char **envpc)
{
	int	i;

	i = 0;
	if (ac == 1)
		return (1);
	while (++i < ac)
	{
		if (is_valid_string(av[i]))
		{
			if (env_var_exists(av[i], envpc))
				;//mod_var_in_envpc_lst
			else
				;//add_var_to_envpc_lst
		}
	}
	return (0);
}
