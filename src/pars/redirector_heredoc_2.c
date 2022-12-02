/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:56:47 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 18:56:46 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hdoc	*ft_hdoc_list_freeone(t_hdoc *hdoc)
{
	int		ret;
	t_hdoc	*next;

	ret = 0;
	next = hdoc->next;
	if (hdoc->next == next)
		ret = 1;
	ft_hdoc_jumpcurrent(hdoc->prev, hdoc->next);
	free(hdoc->file_name);
	hdoc->file_name = NULL;
	free(hdoc);
	hdoc = NULL;
	if (ret == 1)
		return (NULL);
	else
		return (next);
}

int	ft_free_hdoclist(t_hdoc *hdoc)
{
	t_hdoc	*temp;

	if (!hdoc)
		return (1);
	while (1)
	{
		temp = hdoc;
		hdoc = ft_hdoc_jumpcurrent(hdoc->prev, hdoc->next);
		free(temp->file_name);
		free(temp);
		if (hdoc == temp)
			break ;
		temp = NULL;
	}
	hdoc = NULL;
	return (0);
}

int	ft_free_hdoctab(t_hdoc_tab *hdoc_tab)
{
	int	i;

	i = 0;
	if (hdoc_tab)
	{
		while (hdoc_tab[i].file_name)
		{
			free(hdoc_tab[i].file_name);
			hdoc_tab[i].file_name = NULL;
			i++;
		}
		free(hdoc_tab);
		hdoc_tab = NULL;
	}
	return (0);
}

int	ft_count_list(t_hdoc *hdoc)
{
	int		count;
	t_hdoc	*temp;

	count = 0;
	if (!hdoc)
		return (0);
	else
		count++;
	temp = hdoc;
	hdoc = hdoc->next;
	while (hdoc != temp)
	{
		count++;
		hdoc = hdoc->next;
	}
	return (count);
}

t_hdoc_tab	*ft_hdoc_list_to_tab(t_hdoc *hdoc, int count)
{
	int			i;
	t_hdoc_tab	*tab;

	i = 0;
	if (!count)
		return (NULL);
	tab = malloc((count + 1) * sizeof(t_hdoc_tab));
	if (!tab)
		return (ft_msgerr(ERR_MALLOC), NULL);
	while (i < count)
	{
		tab[i].file_name = ft_strdup(hdoc->file_name);
		free(hdoc->file_name);
		tab[i].fd = hdoc->fd;
		hdoc = hdoc->next;
		i++;
	}
	free(hdoc);
	tab[i].file_name = NULL;
	tab[i].fd = 0;
	return (tab);
}
