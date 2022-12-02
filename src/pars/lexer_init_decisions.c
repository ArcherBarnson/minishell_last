/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_decisions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 20:00:34 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_lex_decision_1(t_lex *lex)
{
	lex->decision[NEW_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_SKIP, NEW_LEX_RD_MD, TOK_WORD};
	lex->decision[NEW_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[NEW_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[NEW_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[NEW_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, PIPE_LEX_RD_MD, TOK_PIPE};
	lex->decision[NEW_LEX_RD_MD][AMP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, AMP_LEX_RD_MD, TOK_AMP};
	lex->decision[NEW_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, LT_LEX_RD_MD, TOK_LSS};
	lex->decision[NEW_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, GT_LEX_RD_MD, TOK_GRT};
	lex->decision[NEW_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[NEW_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_END, LEX_SKIP, NEW_LEX_RD_MD, TOK_WORD};
	return (0);
}

int	ft_init_lex_decision_2(t_lex *lex)
{
	lex->decision[STD_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_WORD};
	lex->decision[STD_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[STD_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[STD_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[STD_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, PIPE_LEX_RD_MD, TOK_PIPE};
	lex->decision[STD_LEX_RD_MD][AMP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, AMP_LEX_RD_MD, TOK_AMP};
	lex->decision[STD_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, LT_LEX_RD_MD, TOK_LSS};
	lex->decision[STD_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, GT_LEX_RD_MD, TOK_GRT};
	lex->decision[STD_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[STD_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_END, LEX_SKIP, NEW_LEX_RD_MD, TOK_WORD};
	return (0);
}

int	ft_init_lex_decision_3(t_lex *lex)
{
	lex->decision[SPL_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][AMP_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[SPL_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SPL_ERR_LEX_RD_MD, TOK_WORD};
	return (0);
}

int	ft_init_lex_decision_4(t_lex *lex)
{
	lex->decision[DBL_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][AMP_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[DBL_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, DBL_ERR_LEX_RD_MD, TOK_ERR_DBL};
	return (0);
}

int	ft_init_lex_decision_5(t_lex *lex)
{
	lex->decision[PIPE_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	lex->decision[PIPE_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[PIPE_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[PIPE_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[PIPE_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_WORD};
	lex->decision[PIPE_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[PIPE_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[PIPE_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[PIPE_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	return (0);
}
