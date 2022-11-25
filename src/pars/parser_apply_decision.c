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
        //printf("TOKEN : %s\n", ft_getlabel_token_types(pars->crt_tok_type));
	pars->prev_pars_decision = pars->new_pars_decision;
	pars->new_pars_decision = pars->pars_decision[pars
		->prev_pars_decision.pars_read_mode][pars->crt_tok_type];
	ft_print_debug_pars(pars);
	pars->ft_pars[pars->new_pars_decision.token_action](pars);
	return (pars->ft_pars[pars->new_pars_decision.pars_list_action](pars));
}
