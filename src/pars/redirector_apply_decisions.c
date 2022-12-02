/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_apply_decisions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:52:51 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_apply_decision(t_pars *pars)
{
	int	ret;

	pars->prev_redir_decision = pars->new_redir_decision;
	pars->new_redir_decision = pars->redir_decision[pars
		->prev_redir_decision.redir_read_mode][pars->token->type];
	if (pars->new_redir_decision.token_action == REDIR_IN)
		pars->last_infile_mode = 0;
	else if (pars->new_redir_decision.token_action == REDIR_HDOC)
		pars->last_infile_mode = 1;
	ret = pars->ft_redir[pars->new_redir_decision.token_action](pars);
	if (pars->new_redir_decision.token_action == REDIR_HDOC && ret == 45)
		return (45);
	if (ret)
		return (ret);
	return (pars->ft_redir[pars->new_redir_decision.redir_list_action](pars));
}
