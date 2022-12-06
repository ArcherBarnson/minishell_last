/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:35:18 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/06 09:45:20 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_cmd_link(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->token)
		free_tab(cmd->token);
	return ;
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
	}
	free(tab);
	tab = NULL;
	return ;
}

void	free_all(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmd)
			ft_lstclear(&shell->cmd_head, del);
		if (shell->retprompt)
			free(shell->retprompt);
		if (shell->env_paths)
			free_tab(shell->env_paths);
		if (shell->ms_env)
			free_tab(shell->ms_env);
		if (shell->envpc_head)
			clear_envpc_lst(shell->envpc_head);
		free(shell);
	}
	return ;
}
