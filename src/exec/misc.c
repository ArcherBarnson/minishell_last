/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:42:08 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 20:40:48 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_if_equal(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (str[i] == '=');
}

void	prep_pipexec(int *pids, int tbc)
{
	free(pids);
	child_signals();
	if (tbc > 0)
		close(tbc);
}

void	free_cmd_if(t_shell *shell)
{
	if (shell->cmd && shell->cmd->cmd)
	{
		free(shell->cmd->cmd);
		shell->cmd->cmd = NULL;
	}	
}

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
