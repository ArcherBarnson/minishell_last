/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tools_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:33:54 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 18:34:18 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	del(void *data)
{
	free(data);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_lstdelone(t_cmd *lst, void (*del)(void *))
{
	(void)del;
	if (!lst || !del)
		return ;
	if (lst->cmd)
		lst->cmd = NULL;
	if (lst->token)
	{
		ft_free_tokentab(lst->token, tablen(lst->token));
		lst->token = NULL;
	}
	free(lst);
}

void	ft_lstclear(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*list;
	t_cmd	*tmp;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		ft_lstdelone(list, del);
		list = tmp;
	}
	*lst = NULL;
}
