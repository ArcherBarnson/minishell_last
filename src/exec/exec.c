/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:49:33 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/30 14:30:54 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	exit_code;

void	dup_fds(t_shell *shell)
{
	if (shell->cmd->prev || shell->cmd->fd_in > 0)
	{
		dup2(shell->cmd->fd_in, 0);
		close(shell->cmd->fd_in);
	}
	if (shell->cmd->fd_out != 1)
	{
		dup2(shell->cmd->fd_out, 1);
		close(shell->cmd->fd_out);
	}
	return ;
}

void	execute_command(t_shell *shell, char **envp, int mode)
{
	int	status;

	printf("in %d  out %d    | mode = %d\n", shell->cmd->fd_in, shell->cmd->fd_out, mode);
	if (shell->cmd->fd_in != -1 && shell->cmd->fd_out != -1)
	{
		if (mode == 1)
		{
			status = exec_builtin(shell);
			close_cmd_fds(shell->cmd);
			free(shell->cmd->cmd);
			ft_lstclear(&shell->cmd_head, del);
			shell->cmd = NULL;
			free_all(shell);
			exit(status);
		}
		dup_fds(shell);
		if (shell->cmd->cmd != NULL)
			execve(shell->cmd->cmd, shell->cmd->token, envp);
	}
	free(shell->cmd->cmd);
	shell->cmd->cmd = NULL;
	ft_lstclear(&shell->cmd_head, del);
	shell->cmd = NULL;
	free_all(shell);
}

int	simple_exec(t_shell *shell, char **envp)
{
	int	*pid;
	int	err_code;
	int	is_builtin;

	signal(SIGINT, SIG_IGN);
	is_builtin = check_builtins(shell);
	pid = make_pid_tab(cmds_get_n(shell));
	if (is_builtin == 1)
		return (free(pid), exec_builtin(shell));
	err_code = check_for_invalid_cmd(shell);
	if (err_code)
		return (free(pid), err_code);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		free(pid);
		child_signals();
		execute_command(shell, envp, is_builtin);
		exit(1);
	}
	return (ft_wait(pid, shell));
}

int	pipexec(t_shell *shell, int tbc, char **envp, int *pids)
{
	int	pid;
	int	is_builtin;
	int	err_code;

	err_code = 0;
	signal(SIGINT, SIG_IGN);
	is_builtin = check_builtins(shell);
	if (is_builtin == 2)
		exit(exit_code);
	if (is_builtin == 0)
	{
		err_code = check_for_invalid_cmd(shell);
		if (err_code)
			return (err_code);
	}
	pid = fork();
	if (pid == 0)
	{
		free(pids);
		child_signals();
		if (tbc >= 0)
			close(tbc);
		execute_command(shell, envp, is_builtin);
		exit(1);
	}
	if (shell->cmd && shell->cmd->cmd)
	{
		free(shell->cmd->cmd);
		shell->cmd->cmd = NULL;
	}
	return (pid);
}

int	pipeline(t_shell *shell, char **envp)
{
	int	i;
	int	*pids;

	i = 0;
	pids = make_pid_tab(cmds_get_n(shell));
	shell->cmd = shell->cmd_head;
	while (shell->cmd->next)
	{
		pipe(shell->pipefd);
		if (shell->cmd->fd_out == 1)
			shell->cmd->fd_out = shell->pipefd[1];
		pids[i] = pipexec(shell, shell->pipefd[0], envp, pids);
		printf("apres exec\n");
		if (shell->cmd->fd_in > 0)
			close(shell->cmd->fd_in);
		close(shell->pipefd[1]);
		shell->cmd = shell->cmd->next;
		if (shell->cmd->fd_in == 0)
			shell->cmd->fd_in = shell->pipefd[0];
	}
	pids[i] = pipexec(shell, -1, envp, pids);
	if (shell->cmd->fd_in > 0)
		close(shell->cmd->fd_in);
	return (ft_wait(pids, shell));
}
