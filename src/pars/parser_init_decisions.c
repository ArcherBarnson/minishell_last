/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_decisions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:47:04 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_pars_decision_1(t_pars *pars)
{
	pars->pars_decision[NEW_PARS_RD_MD][TOK_WORD]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, STD_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_NEW]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, STD_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_PIPE]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_AMP]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, AMP_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_LSS]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, LT_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_GRT]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, GT_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_HDOC]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, HDOC_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_GGRT]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, GGRT_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_ERR_SPL]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, GT_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_ERR_DBL]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, GT_PARS_RD_MD};
	pars->pars_decision[NEW_PARS_RD_MD][TOK_END_OF_INPUT]
		= (t_pars_proc){PARS_SKIP, PARS_END, NEW_PARS_RD_MD};
	return (0);
}

int	ft_init_pars_decision_2(t_pars *pars)
{
	pars->pars_decision[STD_PARS_RD_MD][TOK_WORD]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, STD_PARS_RD_MD};
	pars->pars_decision[STD_PARS_RD_MD][TOK_PIPE]
		= (t_pars_proc){PARS_SKIP, PARS_KEEP, NEW_PARS_RD_MD};
	pars->pars_decision[STD_PARS_RD_MD][TOK_AMP]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, AMP_PARS_RD_MD};
	pars->pars_decision[STD_PARS_RD_MD][TOK_LSS]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, LT_PARS_RD_MD};
	pars->pars_decision[STD_PARS_RD_MD][TOK_GRT]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, GT_PARS_RD_MD};
	pars->pars_decision[STD_PARS_RD_MD][TOK_HDOC]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, HDOC_PARS_RD_MD};
	pars->pars_decision[STD_PARS_RD_MD][TOK_GGRT]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, GGRT_PARS_RD_MD};
	pars->pars_decision[STD_PARS_RD_MD][TOK_END_OF_INPUT]
		= (t_pars_proc){PARS_SKIP, PARS_END, NEW_PARS_RD_MD};
	return (0);
}

int	ft_init_pars_decision_3(t_pars *pars)
{
	pars->pars_decision[LT_PARS_RD_MD][TOK_WORD]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, STD_PARS_RD_MD};
	pars->pars_decision[LT_PARS_RD_MD][TOK_PIPE]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[LT_PARS_RD_MD][TOK_LSS]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[LT_PARS_RD_MD][TOK_GRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[LT_PARS_RD_MD][TOK_HDOC]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[LT_PARS_RD_MD][TOK_GGRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[LT_PARS_RD_MD][TOK_END_OF_INPUT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	return (0);
}

int	ft_init_pars_decision_4(t_pars *pars)
{
	pars->pars_decision[GT_PARS_RD_MD][TOK_WORD]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, STD_PARS_RD_MD};
	pars->pars_decision[GT_PARS_RD_MD][TOK_PIPE]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GT_PARS_RD_MD][TOK_LSS]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GT_PARS_RD_MD][TOK_GRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GT_PARS_RD_MD][TOK_HDOC]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GT_PARS_RD_MD][TOK_GGRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GT_PARS_RD_MD][TOK_END_OF_INPUT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	return (0);
}

int	ft_init_pars_decision_5(t_pars *pars)
{
	pars->pars_decision[HDOC_PARS_RD_MD][TOK_WORD]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, STD_PARS_RD_MD};
	pars->pars_decision[HDOC_PARS_RD_MD][TOK_PIPE]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[HDOC_PARS_RD_MD][TOK_LSS]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[HDOC_PARS_RD_MD][TOK_GRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[HDOC_PARS_RD_MD][TOK_HDOC]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[HDOC_PARS_RD_MD][TOK_GGRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[HDOC_PARS_RD_MD][TOK_END_OF_INPUT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	return (0);
}
