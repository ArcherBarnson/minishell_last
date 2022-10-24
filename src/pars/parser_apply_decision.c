/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_apply_decision.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 06:11:11 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pars_apply_decision(t_pars *pars)
{
	//printf("pars->token->name : %s\n", pars->token->id);
	pars->prev_pars_decision = pars->new_pars_decision;
	pars->new_pars_decision = pars->pars_decision[pars
		->prev_pars_decision.pars_read_mode][pars->token->type];
	ft_print_debug_pars(pars);
	if (pars->new_pars_decision.token_action == PARS_ERR)
		return (ft_msgerr(ERR_CASE), 1);
	if (pars->ft_pars[pars->new_pars_decision.token_action](pars))
	{
		return (1);
	}
	pars->ft_pars[pars->new_pars_decision.pars_list_action](pars);
	return (0);
}
