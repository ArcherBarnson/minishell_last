#include "../../inc/minishell.h"

/*void	debug_exec(t_shell *shell)
{
	if (!shell->cmd)
		printf("oh no thats not good \n");
	else
		printf("in +++> %i\nout +++> %i\n\n", shell->cmd->fd_in, shell->cmd->fd_out);
	if (shell->cmd->prev)
		printf("prev_out +++> %i\n", shell->cmd->prev->fd_out);
	if (shell->cmd->next)
		printf("next_in +++> %i\n\n", shell->cmd->next->fd_in);
	return ;
}*/

extern	int exit_code;

int	simple_exec(t_shell *shell, char **envp)
{
	int	*pid;
	int	err_code;
	int	is_builtin;

	signal(SIGINT, SIG_IGN);
	is_builtin = check_builtins(shell);
	if (is_builtin == 2)
		exit(exit_code);
	pid = make_pid_tab(cmds_get_n(shell));
	if (is_builtin == 1 && shell->cmd->fd_out == 1)
		return (exec_builtin(shell));
	err_code = check_for_invalid_cmd(shell);
	if (err_code)
		return (err_code);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		child_signals();
		dup2(shell->cmd->fd_in, STDIN_FILENO);
		dup2(shell->cmd->fd_out, STDOUT_FILENO);
		if (is_builtin == 1)
			exit(exec_builtin(shell));
		else
			execve(shell->cmd->cmd, shell->cmd->token, envp);
	}
	return (ft_wait(pid, shell));
}

void	dup_fds(t_shell *shell)
{
	if (shell->cmd->prev || shell->cmd->fd_in != 0)
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

int	pipexec(t_shell *shell, int tbc, char **envp)
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
		child_signals();
		if (tbc >= 0)
			close(tbc);
		dup_fds(shell);
		if (is_builtin == 0)
			execve(shell->cmd->cmd, shell->cmd->token, envp);
		else
		{
			exec_builtin(shell);
			exit(0);
		}
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
		pids[i] = pipexec(shell, shell->pipefd[0], envp);
		if (shell->cmd->fd_in != 0)
			close(shell->cmd->fd_in);
		close(shell->pipefd[1]);
		shell->cmd = shell->cmd->next;
		if (shell->cmd->fd_in == 0)
			shell->cmd->fd_in = shell->pipefd[0];
	}
	pids[i] = pipexec(shell, -1, envp);
	close(shell->cmd->fd_in);
	return (ft_wait(pids, shell));
}
