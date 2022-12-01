/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init_decisions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 23:42:44 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_exp_decision_1(t_pars *pars)
{
	pars->exp_decision[NEW_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_SKIP, NEW_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[NEW_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[NEW_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_SKIP, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[NEW_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_SKIP, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[NEW_EXP_RD_MD][DOL_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_SKIP, DOL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[NEW_EXP_RD_MD][END_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, NEW_EXP_RD_MD, TOK_WORD};
	return (0);
}

int	ft_init_exp_decision_2(t_pars *pars)
{
	pars->exp_decision[STD_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_SKIP, NEW_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[STD_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[STD_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_REC, EXP_SKIP, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[STD_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_REC, EXP_SKIP, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[STD_EXP_RD_MD][DOL_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_SKIP, DOL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[STD_EXP_RD_MD][END_CHAR]
		= (t_exp_proc){EXP_CATCH, EXP_SKIP, NEW_EXP_RD_MD, TOK_WORD};
	return (0);
}

int	ft_init_exp_decision_3(t_pars *pars)
{
	pars->exp_decision[SPL_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_REC, EXP_SKIP, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][PIPE_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][AMP_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][LT_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][GT_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][DOL_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[SPL_EXP_RD_MD][END_CHAR]
		= (t_exp_proc){EXP_NONE, EXP_SKIP, CMB_ERR_EXP_RD_MD, TOK_ERR_SPL};
	return (0);
}

int	ft_init_exp_decision_4(t_pars *pars)
{
	pars->exp_decision[DBL_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_REC, EXP_SKIP, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][PIPE_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][AMP_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][LT_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][GT_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][DOL_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_SKIP, DOL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DBL_EXP_RD_MD][END_CHAR]
		= (t_exp_proc){EXP_NONE, EXP_SKIP, CMB_ERR_EXP_RD_MD, TOK_ERR_SPL};
	return (0);
}

int	ft_init_exp_decision_5(t_pars *pars)
{
	pars->exp_decision[DOL_EXP_RD_MD][SEP_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_TAKE, STD_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DOL_EXP_RD_MD][STD_CHAR]
		= (t_exp_proc){EXP_KEEP, EXP_TAKE, DOL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DOL_EXP_RD_MD][SPL_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_SKIP, SPL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DOL_EXP_RD_MD][DBL_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_SKIP, DBL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DOL_EXP_RD_MD][DOL_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_SKIP, DOL_EXP_RD_MD, TOK_WORD};
	pars->exp_decision[DOL_EXP_RD_MD][END_CHAR]
		= (t_exp_proc){EXP_DOL, EXP_CATCH, NEW_EXP_RD_MD, TOK_WORD};
	return (0);
}
