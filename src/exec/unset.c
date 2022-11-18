#include "../../inc/minishell.h"

/*int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[i] && s2[i]) && (i < n - 1) && (s1[i] == s2[i]))
		i++;
	if (s1[i] == s2[i])
		return (0);
	return (1);
}*/

/*int	can_unset_var(char *var, t_envp_cpy *envpc_lst)
{
	int	i;
	t_envp_cpy	*head;

	i = 0;
	head = envpc_lst;
	while (envpc_lst->next)
	{
		if (strncmp(var, envpc_lst->var, ft_strlen(var)) == 0)
		{
			while (var[i])
				i++;
			if (envpc_lst->var[i] == '=')
				return (1);
		}
		i = 0;
		envpc_lst = envpc_lst->next;
	}
	envpc_lst = head;
	return (0);
}*/

t_envp_cpy	*remove_var_if_first(int len, char *var, t_envp_cpy *envpc_lst)
{
	t_envp_cpy	*tmp;

	tmp = NULL;
	if (ft_strncmp(var, envpc_lst->var, len) == 0 &&
			envpc_lst->var[len] == '=')
	{
		tmp = envpc_lst;
		if (envpc_lst->next)
			envpc_lst = envpc_lst->next;
		free(tmp->var);
		//free(tmp);
		tmp->var = NULL;
		//tmp = NULL;
	}
	return (envpc_lst);
}

t_envp_cpy	*remove_var_if_present(char *var, int var_len, t_envp_cpy *envpc_lst)
{
	t_envp_cpy	*to_remove;
	t_envp_cpy	*head;

	to_remove = NULL;
	envpc_lst = remove_var_if_first(var_len, var, envpc_lst);
	head = envpc_lst;
	while (envpc_lst->next)
	{
		if (ft_strncmp(var, envpc_lst->next->var, var_len) == 0 &&
			envpc_lst->next->var[var_len] == '=')
		{
			to_remove = envpc_lst->next;
			if (envpc_lst->next->next)
				envpc_lst->next = envpc_lst->next->next;
			else
				envpc_lst->next = NULL;
			free(to_remove->var);
			free(to_remove);
		}
		if (envpc_lst->next != NULL)
			envpc_lst = envpc_lst->next;
	}
	return (head);
}

t_envp_cpy	*unset(int ac, char **av, t_envp_cpy *envpc_lst)
{
	int	i;
	t_envp_cpy	*head;

	i = 1;
	head = NULL;
	if (ac == 1)
		return (envpc_lst);
	while (i < ac)
	{
		head = remove_var_if_present(av[i], ft_strlen(av[i]), envpc_lst);
		envpc_lst = head;
		i++;
	}
	envpc_lst = head;
	if (!envpc_lst->var)
	{
		free(envpc_lst);
		envpc_lst = NULL;
	}
	return (envpc_lst);
}
