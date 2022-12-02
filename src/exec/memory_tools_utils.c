/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tools_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:33:54 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 02:37:02 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	del(void *data)
{
	free(data);
}

void	ft_lstdelone(t_cmd *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->token)
		free_tab(lst->token);
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

void	del2(void *data)
{
	free(data);
}

void	ft_lstdelone2(t_token *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->id)
		free(lst->id);
	free(lst);
}

void	ft_lstclear2(t_token *lst, void (*del)(void *))
{
	t_token	*list;
	t_token	*tmp;

	if (!lst || !del)
		return ;
	list = lst;
	while (list)
	{
		tmp = list->next;
		ft_lstdelone2(list, del);
		list = tmp;
	}
	lst = NULL;
}
