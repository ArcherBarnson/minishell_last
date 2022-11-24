/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:42:08 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/22 09:45:29 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

char	**dup_tab(char **tab)
{
	char	**returntab;
	int		i;

	i = 0;
	returntab = NULL;
	if (!tab)
		return (returntab);
	while (tab[i])
		i++;
	returntab = malloc(sizeof(char *) * (i + 1));
	if (!returntab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		returntab[i] = ft_strdup(tab[i]);
		i++;
	}
	returntab[i] = NULL;
	return (returntab);
}
