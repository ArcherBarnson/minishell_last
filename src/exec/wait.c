/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:27:00 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/23 12:37:19 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		printf("wait pid = %d\n", pid[i]);
		waitpid(pid[i], &exit_code, 0);
		if (WIFSIGNALED(exit_code))
		{
			exit_code = WTERMSIG(exit_code) + 128;
			if (!shell->cmd->next)
				display_signal_intercept(exit_code);
		}
		else if (WIFEXITED(exit_code))
			exit_code = WEXITSTATUS(exit_code);
		printf("code = %d\n", exit_code);
		i++;
	}
	free(pid);
	ft_lstclear(&shell->cmd_head, del);
	shell->cmd_head = NULL;
	return (exit_code);
}
