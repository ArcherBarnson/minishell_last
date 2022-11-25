/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_apply_decisions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/25 12:40:48 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_apply_decision(t_pars *pars)
{
	pars->prev_redir_decision = pars->new_redir_decision;
	pars->new_redir_decision = pars->redir_decision[pars
		->prev_redir_decision.redir_read_mode][pars->token->type];
	ft_print_debug_redir(pars);
	//if (pars->new_redir_decision.token_action == REDIR_ERR)
	//	return (ft_msgerr(ERR_CASE), 1);
	pars->ft_redir[pars->new_redir_decision.token_action](pars);
	return (pars->ft_redir[pars->new_redir_decision.redir_list_action](pars));
}
