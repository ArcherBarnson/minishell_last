/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:25:21 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/06 11:12:30 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmds_get_n(t_shell *shell)
{
	int	n;

	n = 0;
	shell->cmd = shell->cmd_head;
	while (shell->cmd && shell->cmd->next)
	{
		n++;
		shell->cmd = shell->cmd->next;
	}
	n++;
	shell->cmd = shell->cmd_head;
	return (n);
}

int	check_for_invalid_cmd(t_shell *shell)
{
	int	fd;

	if (!shell || !shell->cmd || !shell->cmd->token || !shell->cmd->token[0])
		return (1);
	if (shell->cmd->token[0][0] == '.' && shell->cmd->token[0][1] == '\0')
	{
		write(2, "msh : .:filename argument required\n", 36);
		write(2, ".: usage . filename[arguments]\n", 31);
		return (2);
	}
	fd = open(shell->cmd->token[0], O_DIRECTORY);
	if (fd != -1)
	{
		write(2, shell->cmd->token[0], ft_strlen(shell->cmd->token[0]));
		write(2, " : is a directory\n", 19);
		close(fd);
		return (126);
	}
	shell->cmd->cmd = find_path(shell->cmd->token[0], shell->env_paths);
	return (command_not_found(shell));
}

int	command_not_found(t_shell *shell)
{
	int	tmp_fd;

	tmp_fd = 0;
	if (!is_valid_history(shell->retprompt))
		return (1);
	if (shell->cmd->cmd == NULL)
	{
		write(2, shell->cmd->token[0], ft_strlen(shell->cmd->token[0]));
		write(2, " : Command not found\n", 21);
		shell->exit_status = 127;
		return (127);
	}
	tmp_fd = open(shell->cmd->cmd, O_RDONLY);
	if (tmp_fd == -1 && errno == EACCES)
	{
		write(2, shell->cmd->token[0], ft_strlen(shell->cmd->token[0]));
		write(2, " : permission denied\n", 22);
		shell->exit_status = 126;
		return (126);
	}
	if (tmp_fd > 0)
		close(tmp_fd);
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

void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
	}
	return ;
}
