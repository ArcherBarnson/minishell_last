/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_apply_decisions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 14:36:36 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exp_apply_decision(t_pars *pars)
{
	pars->prev_exp_decision = pars->new_exp_decision;
	pars->new_exp_decision = pars->exp_decision[pars
		->prev_exp_decision.exp_read_mode][ft_char_type(pars->parser_text[0])];
	ft_print_debug_exp(pars);
	if (pars->new_exp_decision.buffer_action == EXP_ERR)
		return (ft_msgerr(ERR_CASE), 1);
	pars->ft_exp[pars->new_exp_decision.buffer_action](pars);
	pars->ft_exp[pars->new_exp_decision.char_action](pars);
	return (0);
}
