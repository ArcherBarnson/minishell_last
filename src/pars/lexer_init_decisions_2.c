/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_decisions_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:44:34 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 20:00:44 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_lex_decision_6(t_lex *lex)
{
	lex->decision[LT_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	lex->decision[LT_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[LT_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[LT_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[LT_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[LT_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, HDOC_LEX_RD_MD, TOK_HDOC};
	lex->decision[LT_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_WORD};
	lex->decision[LT_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[LT_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	return (0);
}

int	ft_init_lex_decision_7(t_lex *lex)
{
	lex->decision[GT_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	lex->decision[GT_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[GT_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[GT_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[GT_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[GT_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[GT_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_KEEP, LEX_TAKE, GGRT_LEX_RD_MD, TOK_GGRT};
	lex->decision[GT_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[GT_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	return (0);
}

int	ft_init_lex_decision_8(t_lex *lex)
{
	lex->decision[HDOC_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	lex->decision[HDOC_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[HDOC_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[HDOC_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[HDOC_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[HDOC_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[HDOC_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[HDOC_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[HDOC_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	return (0);
}

int	ft_init_lex_decision_9(t_lex *lex)
{
	lex->decision[GGRT_LEX_RD_MD][SEP_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, NEW_LEX_RD_MD, TOK_NEW};
	lex->decision[GGRT_LEX_RD_MD][STD_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[GGRT_LEX_RD_MD][SPL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, SPL_LEX_RD_MD, TOK_WORD};
	lex->decision[GGRT_LEX_RD_MD][DBL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_SKIP, DBL_LEX_RD_MD, TOK_WORD};
	lex->decision[GGRT_LEX_RD_MD][PIPE_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[GGRT_LEX_RD_MD][LT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[GGRT_LEX_RD_MD][GT_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	lex->decision[GGRT_LEX_RD_MD][DOL_CHAR]
		= (t_lex_proc){LEX_CATCH, LEX_TAKE, STD_LEX_RD_MD, TOK_WORD};
	lex->decision[GGRT_LEX_RD_MD][END_CHAR]
		= (t_lex_proc){LEX_NONE, LEX_ERR, SYN_ERR_LEX_RD_MD, TOK_NEW};
	return (0);
}
