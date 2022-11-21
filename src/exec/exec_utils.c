/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:25:21 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/21 11:49:48 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmds_get_n(t_shell *shell)
{
	int	n;

	n = 0;
	shell->cmd = shell->cmd_head;
	while (shell->cmd->next)
	{
		n++;
		shell->cmd = shell->cmd->next;
	}
	n++;
	shell->cmd = shell->cmd_head;
	//printf("GETSIZE_DEBUG => %i\n", n);
	return (n);
}

int	command_not_found(t_shell *shell)
{
	if (!is_valid_history(shell->retprompt))
		return (-1);
	if (shell->cmd->cmd == NULL)
	{
		write(2, shell->cmd->token[0], ft_strlen(shell->cmd->token[0]));
		write(2, " : Command not found\n", 21);
		shell->exit_status = 127;
		return (-1);
	}
	return (0);
}

int	*make_pid_tab(int size)
{
	int	*pids;
	int	i;

	i = -1;
	if (size < 1)
		return (NULL);
	pids = malloc(sizeof(int) * (size + 1));
	if (!pids)
		return (NULL);
	while (++i <= size)
		pids[i] = 0;
	return (pids);
}
