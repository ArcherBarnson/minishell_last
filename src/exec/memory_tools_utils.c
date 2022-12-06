/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tools_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:33:54 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/06 09:51:19 by bgrulois         ###   ########.fr       */
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
	if (lst->token != NULL)
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
