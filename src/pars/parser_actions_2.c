/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_actions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:45:42 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:46:10 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pars_drop(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_pars_take(t_pars *pars)
{
	if (pars->prev_pars_decision.pars_read_mode == NEW_PARS_RD_MD
		|| pars->prev_pars_decision.pars_read_mode == PIPE_PARS_RD_MD)
	{
		ft_pars_new(pars);
	}
	else
	{
		pars->command->token = ft_token_addnext(pars->command->token,
				ft_new_token(pars->token->id));
		pars->command->nb_of_tokens++;
	}
	pars->command->token->type = pars->token->type;
	return (0);
}

int	ft_pars_skip(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_pars_record(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_pars_end(t_pars *pars)
{
	(void)pars;
	return (0);
}
