/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_initializations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:18:49 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:29:42 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_lex_decisions(t_lex *lex)
{
	ft_init_lex_decision_1(lex);
	ft_init_lex_decision_2(lex);
	ft_init_lex_decision_3(lex);
	ft_init_lex_decision_4(lex);
	ft_init_lex_decision_5(lex);
	ft_init_lex_decision_6(lex);
	ft_init_lex_decision_7(lex);
	ft_init_lex_decision_8(lex);
	ft_init_lex_decision_9(lex);
	return (0);
}

int	ft_init_pars_decisions(t_pars *pars)
{
	ft_init_pars_decision_1(pars);
	ft_init_pars_decision_2(pars);
	ft_init_pars_decision_3(pars);
	ft_init_pars_decision_4(pars);
	ft_init_pars_decision_5(pars);
	ft_init_pars_decision_6(pars);
	ft_init_pars_decision_7(pars);
	return (0);
}

int	ft_init_exp_decisions(t_pars *pars)
{
	ft_init_exp_decision_1(pars);
	ft_init_exp_decision_2(pars);
	ft_init_exp_decision_3(pars);
	ft_init_exp_decision_4(pars);
	ft_init_exp_decision_5(pars);
	ft_init_exp_decision_6(pars);
	ft_init_exp_decision_7(pars);
	ft_init_exp_decision_8(pars);
	return (0);
}

int	ft_init_redir_decisions(t_pars *pars)
{
	ft_init_redir_decision_1(pars);
	ft_init_redir_decision_2(pars);
	ft_init_redir_decision_3(pars);
	return (0);
}

int	ft_init_first_lex_decisions(t_lex *lex)
{
	lex->new_decision = (t_lex_proc)
	{LEX_ERR, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	lex->prev_decision = (t_lex_proc)
	{LEX_ERR, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	return (0);
}
