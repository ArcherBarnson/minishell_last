/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ctl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:44:46 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/29 21:17:45 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin(t_shell *shell, int fork)
{
	if (ft_strcmp(shell->cmd->token[0], UNSET) == 1)
		return (unset(get_tab_size(shell->cmd->token),
				shell->cmd->token, &(shell->envpc)));
	if (ft_strcmp(shell->cmd->token[0], PWD) == 1)
		return (pwd(get_tab_size(shell->cmd->token),
				shell->cmd->token, shell->cmd->fd_out));
	if (ft_strcmp(shell->cmd->token[0], ECHO) == 1)
		return (echo(get_tab_size(shell->cmd->token),
				shell->cmd->token, shell->cmd->fd_out));
	if (ft_strcmp(shell->cmd->token[0], CD) == 1)
		return (cd(shell, shell->cmd->token,
				shell->ms_env, &(shell->envpc)));
	if (ft_strcmp(shell->cmd->token[0], EXPORT) == 1)
		return (export(shell, shell->cmd->token,
				&(shell->envpc)));
	if (ft_strcmp(shell->cmd->token[0], ENV) == 1)
		return (env(shell, shell->ms_env, 0));
	if (ft_strcmp(shell->cmd->token[0], EXIT) == 1)
		return (ft_exit(get_tab_size(shell->cmd->token),
				shell->cmd->token, shell, fork));
	return (-1);
}

int	check_builtins(t_shell *shell)
{
	if (!shell->cmd)
		return (0);
	if (ft_strcmp(shell->cmd->token[0], ECHO) == 1
		|| ft_strcmp(shell->cmd->token[0], EXIT) == 1
		|| ft_strcmp(shell->cmd->token[0], ENV) == 1
		|| ft_strcmp(shell->cmd->token[0], EXPORT) == 1
		|| ft_strcmp(shell->cmd->token[0], UNSET) == 1
		|| ft_strcmp(shell->cmd->token[0], PWD) == 1
		||ft_strcmp(shell->cmd->token[0], CD) == 1)
		return (1);
	return (0);
}
