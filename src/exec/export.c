#include "../../inc/minishell.h"

int	export_error(char *str, int i, int error_type)
{
	if (error_type == 0)
	{
		write(2, "Needs a variable name before '=' operator\n", 43);
		return (0);
	}
	if (error_type == 1)
	{
		write(2, &str[i], 1);
		write(2, " : Invalid identifier before '='\n", 34);
		return (0);
	}
	return (0);
}

int	is_env_var(char *str)
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
		(c < '0' || c > '9') && c != '_')
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

int	ft_strccmp(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] != c && s2[i] != c && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	return (1);
}

int	env_var_exists(char *str, char **envpc)
{
	int	i;

	i = 0;
	if (!str || !envpc)
		return (0);
	while (envpc[i] != NULL)
	{
		if (ft_strccmp(str, envpc[i], '=') == 0)
			return (1);
		i++;
	}
	return (0);
}


void	mod_env_var(char *var, t_envp_cpy *envpc_lst)
{
	while (envpc_lst->next && ft_strccmp(var, envpc_lst->var, '=') != 0)
		envpc_lst = envpc_lst->next;
	free(envpc_lst->var);
	envpc_lst->var = ft_strdup(var);
	return ;
}

int	export(int ac, char **av, char **envpc, t_envp_cpy *envpc_lst)
{
	int	i;

	i = 1;
	if (ac == 1)
		return (1);
	while (i < ac)
	{
		if (is_valid_string(av[i]))
		{
			printf("\n\nav[%i] == %s\n\n", i, av[i]);
			if (env_var_exists(av[i], envpc))
				mod_env_var(av[i], envpc_lst);
			else
				ft_env_varadd_back(envpc_lst,
					ft_envpcnew(ft_strdup(av[i])));
		}
		i++;
	}
	return (0);
}
