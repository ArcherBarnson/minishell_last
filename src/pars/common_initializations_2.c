/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_initializations_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:29:48 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:58:00 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_first_pars_decisions(t_pars *pars)
{
	pars->new_pars_decision = (t_pars_proc)
	{PARS_SKIP, PARS_ERR, NEW_PARS_RD_MD};
	pars->prev_pars_decision = (t_pars_proc)
	{PARS_SKIP, PARS_ERR, NEW_PARS_RD_MD};
	pars->new_exp_decision = (t_exp_proc)
	{EXP_ERR, EXP_SKIP, NEW_EXP_RD_MD, TOK_NEW};
	pars->prev_exp_decision = (t_exp_proc)
	{EXP_ERR, EXP_SKIP, NEW_EXP_RD_MD, TOK_NEW};
	pars->new_redir_decision = (t_redir_proc)
	{REDIR_SKIP, REDIR_ERR, NEW_REDIR_RD_MD};
	pars->prev_redir_decision = (t_redir_proc)
	{REDIR_SKIP, REDIR_ERR, NEW_REDIR_RD_MD};
	return (0);
}

int	ft_general_initialize(t_lex *lex, t_pars *pars)
{
	ft_init_lex_decisions(lex);
	ft_init_pars_decisions(pars);
	ft_init_exp_decisions(pars);
	ft_init_redir_decisions(pars);
	ft_init_first_lex_decisions(lex);
	ft_init_first_pars_decisions(pars);
	ft_init_lex_actions(lex);
	ft_init_pars_actions(pars);
	ft_init_exp_actions(pars);
	ft_init_redir_actions(pars);
	return (0);
}

int	ft_init_expander(t_pars *pars)
{
	pars->offset_start = 0;
	pars->start_std = 0;
	pars->start_dol = 0;
	pars->nb_taken_char = 0;
	return (0);
}

int	ft_init_pars_counts(t_pars *pars)
{
	pars->i = 0;
	pars->j = 0;
	pars->k = 0;
	pars->count = 0;
	pars->r = 0;
	return (0);
}
