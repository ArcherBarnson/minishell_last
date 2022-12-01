/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_apply_decisions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 23:45:20 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_apply_decision(t_shell *shell)
{
	shell->pars->prev_redir_decision = shell->pars->new_redir_decision;
	shell->pars->new_redir_decision = shell->pars->redir_decision[shell->pars
		->prev_redir_decision.redir_read_mode][shell->pars->token->type];
	ft_debug_redir(shell->pars);
	if (shell->pars->new_redir_decision.token_action == REDIR_IN)
		shell->pars->last_infile_mode = 0;
	else if (shell->pars->new_redir_decision.token_action == REDIR_HDOC)
		shell->pars->last_infile_mode = 1;
	shell->pars->ft_redir[shell->pars->new_redir_decision.token_action](shell);
	return (shell->pars->ft_redir[shell->pars
			->new_redir_decision.redir_list_action](shell));
}
