/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:35:18 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/18 13:49:51 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_cmd_link(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->token)
	{
		while (cmd->token[++i])
			free(cmd->token[i]);
		free(cmd->token);
	}
	free(cmd);
	return ;
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
		cmd = NULL;
		//free_cmd_link(cmd);
	}
	return ;
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return ;
}

void	free_all(t_shell *shell)
{
	if (shell)
	{
		if (shell->cmd != NULL)
			free_cmd_lst(shell->cmd);
		if (shell->retprompt)
			free(shell->retprompt);
		if (shell->env_paths)
			free_tab(shell->env_paths);
		if (shell->ms_env)
			free_tab(shell->ms_env);
		if (shell->envpc_head)
			clear_envpc_lst(shell->envpc_head);
		if (shell->pars != NULL)
		{
			ft_execfree_freeall(shell->pars);
			ft_pars_freeall(shell->pars);
		}
		free(shell);
	}
	return ;
}

/*void	bzero_i_guess(char *buf)
{
	int	i;
	int	size;

	i = -1;
	size = ft_strlen(buf);
	while (++i < size)
		buf[i] = '\0';
	return ;
}*/
