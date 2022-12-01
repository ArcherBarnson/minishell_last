/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init_decisions_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:41:22 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:41:25 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_exp_decision_6(t_pars *pars)
{
	pars->exp_decision[PIPE_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, NEW_EXP_RD_MD, TOK_NEW};
	pars->exp_decision[PIPE_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_TAKE, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[PIPE_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[PIPE_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[PIPE_EXP_RD_MD][ESCP_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, ESCP_EXP_RD_MD, TOK_NEW};
	return (0);
}

int	ft_init_exp_decision_7(t_pars *pars)
{
	pars->exp_decision[LT_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, NEW_EXP_RD_MD, TOK_NEW};
	pars->exp_decision[LT_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_TAKE, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[LT_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[LT_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[LT_EXP_RD_MD][ESCP_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, ESCP_EXP_RD_MD, TOK_NEW};
	pars->exp_decision[LT_EXP_RD_MD][LT_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, HDOC_EXP_RD_MD, TOK_HDOC};
	return (0);
}

int	ft_init_exp_decision_8(t_pars *pars)
{
	pars->exp_decision[GT_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, NEW_EXP_RD_MD, TOK_NEW};
	pars->exp_decision[GT_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_TAKE, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[GT_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[GT_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[GT_EXP_RD_MD][GT_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, GGRT_EXP_RD_MD, TOK_GGRT};
	return (0);
}

int	ft_init_exp_decision_9(t_pars *pars)
{
	(void)pars;
	return (0);
}
