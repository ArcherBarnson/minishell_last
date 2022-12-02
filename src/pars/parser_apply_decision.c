/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_apply_decision.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:59:17 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pars_apply_decision(t_pars *pars)
{
	pars->prev_pars_decision = pars->new_pars_decision;
	pars->new_pars_decision = pars->pars_decision[pars
		->prev_pars_decision.pars_read_mode][pars->crt_tok_type];
	pars->ft_pars[pars->new_pars_decision.token_action](pars);
	return (pars->ft_pars[pars->new_pars_decision.pars_list_action](pars));
}
