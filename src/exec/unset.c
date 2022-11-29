/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:38:41 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 17:39:28 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_envp_cpy	*remove_var_if_first(int len, char *var, t_envp_cpy *envpc_lst)
{
	t_envp_cpy	*tmp;

	tmp = NULL;
	if (ft_strncmp(var, envpc_lst->var, len) == 0)
	{
		tmp = envpc_lst;
		if (envpc_lst->next)
			envpc_lst = envpc_lst->next;
		free(tmp->var);
		tmp->var = NULL;
	}
	return (envpc_lst);
}

t_envp_cpy	*remove_var_if_present(char *var, int len, t_envp_cpy *envpc_lst)
{
	t_envp_cpy	*to_remove;
	t_envp_cpy	*head;

	to_remove = NULL;
	envpc_lst = remove_var_if_first(len, var, envpc_lst);
	head = envpc_lst;
	while (envpc_lst->next)
	{
		if (ft_strncmp(var, envpc_lst->next->var, len) == 0)
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
	int						i;
	t_envp_cpy				*head;

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
