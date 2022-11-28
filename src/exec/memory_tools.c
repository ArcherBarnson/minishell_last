/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:35:18 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 13:11:19 by jtaravel         ###   ########.fr       */
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

void	free_cmd_lst(t_cmd *cmd)
{
	if (cmd)
	{
		while (cmd->prev != NULL)
			cmd = cmd->prev;
		while (cmd->next != NULL)
		{
			if (cmd->prev)
				free_cmd_link(cmd->prev);
			cmd = cmd->next;
		}
		if (cmd->prev)
			free_cmd_link(cmd->prev);
		if (cmd)
			free_cmd_link(cmd);
		free(cmd);
		cmd = NULL;
	}
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
			free(tab[i]);
	}
	free(tab);
	return ;
}

void	free_all(t_shell *shell)
{
	if (shell)
	{
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
