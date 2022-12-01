/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpc_lst_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 07:54:56 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/01 11:14:41 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_envp_cpy	*ft_envpcnew(char *var)
{
	t_envp_cpy	*new;

	new = malloc(sizeof(t_envp_cpy));
	if (!new)
		return (NULL);
	new->var = ft_strdup(var);
	new->next = NULL;
	return (new);
}

void	ft_env_varadd_back(t_envp_cpy **envpc_lst, t_envp_cpy *new)
{
	if (!new || !envpc_lst)
		return ;
	if (!(*envpc_lst))
	{
		*envpc_lst = new;
		return ;
	}
	while ((*envpc_lst)->next)
		*envpc_lst = (*envpc_lst)->next;
	(*envpc_lst)->next = new;
}

/*void	del(void *data)
{
	free(data);
}

void	ft_lstdel_envpc(t_envp_cpy *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->var)
		(*del)(lst->var);
	free(lst);
}

void	ft_envpc_clear(t_envp_cpy **lst, void (*del)(void *))
{
	t_envp_cpy	*list;
	t_envp_cpy	*tmp;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		ft_lstdel_envpc(list, del);
		list = tmp;
	}
	*lst = NULL;
}*/

void	clear_envpc_lst(t_envp_cpy *envpc_lst)
{
	t_envp_cpy *tmp;

	if (!envpc_lst)
		return ;
	while (envpc_lst)
	{
		tmp = envpc_lst;
		envpc_lst = envpc_lst->next;
		free(tmp->var);
		free(tmp);
	}
	return ;
}
