/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_apply_decisions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/28 18:39:29 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_apply_decision(t_pars *pars)
{
	//printf("[1] : %s\n", ft_getlabel_redir_read_modes
	//	(pars->prev_redir_decision.redir_read_mode));
	//printf("[2] : %d\n", pars->token->type);
	//printf("[2] : %s\n", ft_getlabel_token_types(pars->token->type));
	pars->prev_redir_decision = pars->new_redir_decision;
	pars->new_redir_decision = pars->redir_decision[pars
		->prev_redir_decision.redir_read_mode][pars->token->type];
	//ft_print_debug_redir(pars);
	//if (pars->new_redir_decision.token_action == REDIR_ERR)
	//	return (ft_msgerr(ERR_CASE), 1);
	pars->ft_redir[pars->new_redir_decision.token_action](pars);
	return (pars->ft_redir[pars->new_redir_decision.redir_list_action](pars));
}
