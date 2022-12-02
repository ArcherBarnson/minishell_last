/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:34:23 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 20:17:45 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exp_catch(t_pars *pars)
{
	ft_exp_record(pars);
	if (pars->temp)
	{
		free(pars->token->id);
		pars->token->id = NULL;
		pars->token->id = ft_strdup(pars->temp);
		pars->token->type = pars->prev_exp_decision.token_type;
		free(pars->temp);
		pars->temp = NULL;
	}
	else
	{
		free(pars->token->id);
		pars->token->id = NULL;
		pars->token->id = ft_strdup("");
		pars->token->type = pars->prev_exp_decision.token_type;
	}
	return (0);
}

int	ft_exp_keep(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_drop(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_take(t_pars *pars)
{
	if (!pars->nb_taken_char)
		pars->start_std = pars->offset_start;
	pars->nb_taken_char++;
	if (pars->nb_taken_char == 1 && !ft_strncmp(pars->parser_text, "?", 1))
		ft_exp_dol(pars);
	return (0);
}

int	ft_exp_skip(t_pars *pars)
{
	(void)pars;
	return (0);
}
