/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_apply_decisions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 21:55:21 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_apply_decision(t_shell *shell)
{
	shell->pars->prev_redir_decision = shell->pars->new_redir_decision;
	//printf("[1] : %s\n", ft_getlabel_redir_read_modes
	//	(shell->pars->prev_redir_decision.redir_read_mode));
	if (g_exit_code == 199 || g_exit_code == 130 || g_exit_code == 678)
	{
		shell->pars->token->type = 0;
		g_exit_code = 0;
	}
	//printf("[2] : %s\n", ft_getlabel_token_types(shell->pars->token->type));
	shell->pars->new_redir_decision = shell->pars->redir_decision[shell->pars
		->prev_redir_decision.redir_read_mode][shell->pars->token->type];
	//ft_debug_redir(shell->pars);
	if (shell->pars->new_redir_decision.token_action == REDIR_IN)
		shell->pars->last_infile_mode = 0;
	else if (shell->pars->new_redir_decision.token_action == REDIR_HDOC)
		shell->pars->last_infile_mode = 1;
	shell->pars->ft_redir[shell->pars->new_redir_decision.token_action](shell);
	return (shell->pars->ft_redir[shell->pars
			->new_redir_decision.redir_list_action](shell));
}
