/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 05:06:28 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/24 13:51:28 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_envp_lst_size(t_envp_cpy *envpc_lst)
{
	int	n;

	n = 0;
	if (!envpc_lst)
		return (n);
	while (envpc_lst->next != NULL)
	{
		n++;
		envpc_lst = envpc_lst->next;
	}
	printf("lst_size_debug +++> %i\n", n);
	return (n);
}

t_envp_cpy	*envp_to_lst(char **envp)
{
	int	i;
	t_envp_cpy	*envpc_lst;

	i = 0;
	envpc_lst = malloc(sizeof(t_envp_cpy));
	if (!envpc_lst)
		return (NULL);
	while (envp[i] != NULL)
	{
		//envpc_lst->var = ft_strdup(envp[i]);
		ft_env_varadd_back(envpc_lst, ft_envpcnew(ft_strdup(envp[i])));
		envpc_lst = envpc_lst->next;
		i++;
	}
	envpc_lst->next = NULL;
	return (envpc_lst);
}

char	**lst_to_envp(t_envp_cpy *envpc_lst)
{
	int	i;
	int	lst_size;
	char	**envpc;
	t_envp_cpy	*envpc_lst_head;

	i = 0;
	envpc_lst_head = envpc_lst;
	lst_size = get_envp_lst_size(envpc_lst);
	envpc = malloc(sizeof(char *) * lst_size + 1);
	if (!envpc)
		return (NULL);
	while (envpc_lst->next != NULL)
	{
		envpc[i] = ft_strdup(envpc_lst->var);
		envpc_lst = envpc_lst->next;
		i++;
	}
	envpc[i] = NULL;
	clear_envpc_lst(envpc_lst_head);
	return (envpc);
}
