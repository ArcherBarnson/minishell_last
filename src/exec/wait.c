/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:27:00 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/06 13:00:15 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_end_wait(t_shell *shell, int *pid)
{
	free(pid);
	ft_lstclear(&shell->cmd_head, del);
	shell->cmd_head = NULL;
}

int	ft_wait(int *pid, t_shell *shell)
{
	int	exit_code;
	int	i;
	int	ncmds;

	i = 0;
	exit_code = 0;
	ncmds = cmds_get_n(shell);
	while (i < ncmds)
	{
		waitpid(pid[i], &exit_code, 0);
		if (WIFSIGNALED(exit_code))
		{
			exit_code = WTERMSIG(exit_code) + 128;
			if (exit_code == 141)
				exit_code = 127;
			if (!shell->cmd->next)
				display_signal_intercept(exit_code);
		}
		else if (WIFEXITED(exit_code))
			exit_code = WEXITSTATUS(exit_code);
		i++;
	}
	ft_end_wait(shell, pid);
	return (exit_code);
}
