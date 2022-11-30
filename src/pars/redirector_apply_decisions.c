/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_apply_decisions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/30 10:51:38 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_apply_decision(t_pars *pars)
{
	pars->prev_redir_decision = pars->new_redir_decision;
	pars->new_redir_decision = pars->redir_decision[pars
		->prev_redir_decision.redir_read_mode][pars->token->type];
	pars->ft_redir[pars->new_redir_decision.token_action](pars);
	return (pars->ft_redir[pars->new_redir_decision.redir_list_action](pars));
}
