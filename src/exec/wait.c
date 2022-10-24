/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:27:00 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/18 13:43:28 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_wait(int *pid, t_shell *shell)
{
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (i <= cmds_get_n(shell))
	{
		waitpid(pid[i], &exit_code, 0);
		if (WIFSIGNALED(exit_code))
		{
			exit_code = WTERMSIG(exit_code) + 128;
			if (!shell->cmd->next)
				display_signal_intercept(exit_code);
		}
		else if (WIFEXITED(exit_code))
			exit_code = WEXITSTATUS(exit_code);
		i++;
	}
	return (exit_code);
}
