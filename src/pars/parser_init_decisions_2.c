/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init_decisionsi_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:47:07 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:47:19 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_pars_decision_6(t_pars *pars)
{
	pars->pars_decision[GGRT_PARS_RD_MD][TOK_WORD]
		= (t_pars_proc){PARS_TAKE, PARS_KEEP, STD_PARS_RD_MD};
	pars->pars_decision[GGRT_PARS_RD_MD][TOK_PIPE]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GGRT_PARS_RD_MD][TOK_LSS]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GGRT_PARS_RD_MD][TOK_GRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GGRT_PARS_RD_MD][TOK_HDOC]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GGRT_PARS_RD_MD][TOK_GGRT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	pars->pars_decision[GGRT_PARS_RD_MD][TOK_END_OF_INPUT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	return (0);
}

int	ft_init_pars_decision_7(t_pars *pars)
{
	(void)pars;
	pars->pars_decision[PIPE_PARS_RD_MD][TOK_WORD]
		= (t_pars_proc){PARS_TAKE, PARS_TAKE, STD_PARS_RD_MD};
	pars->pars_decision[PIPE_PARS_RD_MD][TOK_LSS]
		= (t_pars_proc){PARS_TAKE, PARS_TAKE, LT_PARS_RD_MD};
	pars->pars_decision[PIPE_PARS_RD_MD][TOK_HDOC]
		= (t_pars_proc){PARS_TAKE, PARS_TAKE, HDOC_PARS_RD_MD};
	pars->pars_decision[PIPE_PARS_RD_MD][TOK_END_OF_INPUT]
		= (t_pars_proc){PARS_NONE, PARS_ERR, SYN_ERR_PARS_RD_MD};
	return (0);
}
