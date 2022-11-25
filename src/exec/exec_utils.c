/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:25:21 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/25 10:26:18 by bgrulois         ###   ########.fr       */
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

int	check_for_invalid_cmd(t_shell *shell)
{
	if (!shell->cmd->token || !shell->cmd->token[0])
		return (0);
	if (shell->cmd->token[0][0] == '.' && shell->cmd->token[0][1] == '\0')
	{
		write(2, shell->cmd->cmd, ft_strlen(shell->cmd->token[0]));
		write(2, ": usage . filename[arguments]\n", 29);
		return (2);
	}
	if (open(shell->cmd->token[0], O_DIRECTORY) != -1)
	{
		write(2, shell->cmd->token[0], ft_strlen(shell->cmd->token[0]));
		write(2, " : is a directory\n", 19);
		return (126);
	}
	shell->cmd->cmd = find_path(shell->cmd->token[0], shell->env_paths);
	if (command_not_found(shell))
		return (127);
	return (0);
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
		return (127);
	}
	if (open(shell->cmd->cmd, O_RDONLY) == -1 && errno == EACCES)
	{
		write(2, shell->cmd->token[0], ft_strlen(shell->cmd->token[0]));
		write(2, " : permission denied\n", 22);
		shell->exit_status = 126;
		return (126);
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
