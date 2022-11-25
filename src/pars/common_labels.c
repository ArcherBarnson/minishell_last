/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_labels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:18:49 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 18:20:14 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getlabel_error_msgs(const t_err_codes index)
{
	static const char	*label[LEN_ERR_CODES] = {
		"ERR_CD_CMB", "ERR_CD_SYN", "ERR_CD_CHR",
		"ERR_CD_SPL", "ERR_CD_DBL"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_error_msgs_txt(const t_err_codes index)
{
	static const char	*label[LEN_ERR_CODES] = {
		ERR_CMB, ERR_SYN, ERR_CHR, ERR_SPL, ERR_DBL
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_token_types(const t_token_types index)
{
	static const char	*label[LEN_TOKEN_TYPES] = {
		"TOK_NEW", "TOK_WORD", "TOK_NEW_LINE", "TOK_LSS", "TOK_GRT",
		"TOK_GGRT", "TOK_HDOC", "TOK_PIPE", "TOK_AMP", "TOK_OP_OR",
		"TOK_OP_AND", "TOK_ERR_MARK", "TOK_ERR_SPL", "TOK_ERR_DBL",
		"TOK_END_OF_INPUT"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_char_types(const t_char_types index)
{
	static const char	*label[LEN_CHAR_TYPES] = {
		"ERR_CHAR", "SEP_CHAR", "STD_CHAR", "SPL_CHAR", "DBL_CHAR",
		"ESCP_CHAR", "PIPE_CHAR", "AMP_CHAR", "LT_CHAR", "GT_CHAR", "DOL_CHAR",
		"END_CHAR"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_lex_actions(const t_lex_actions index)
{
	static const char	*label[LEN_LEX_ACTIONS] = {
		"LEX_ERR", "LEX_NONE", "LEX_CATCH", "LEX_KEEP", "LEX_DROP",
		"LEX_TAKE", "LEX_SKIP", "LEX_REC", "LEX_END"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_pars_actions(const t_pars_actions index)
{
	static const char	*label[LEN_PARS_ACTIONS] = {
		"PARS_ERR", "PARS_NONE", "PARS_NEW", "PARS_CATCH",
		"PARS_KEEP", "PARS_DROP", "PARS_TAKE", "PARS_SKIP", "PARS_END"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_exp_actions(const t_exp_actions index)
{
	static const char	*label[LEN_EXP_ACTIONS] = {
		"EXP_ERR", "EXP_NONE", "EXP_NEW", "EXP_CATCH", "EXP_KEEP",
		"EXP_REC", "EXP_DROP", "EXP_TAKE", "EXP_SKIP", "EXP_END", "EXP_DOL",
		"EXP_ERR_DBL", "EXP_ANALYSIS"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_redir_actions(const t_redir_actions index)
{
	static const char	*label[LEN_REDIR_ACTIONS] = {
		"REDIR_ERR", "REDIR_NONE", "REDIR_NEW", "REDIR_CATCH", "REDIR_KEEP",
		"REDIR_DROP", "REDIR_TAKE", "REDIR_SKIP", "REDIR_IN", "REDIR_HDOC",
		"REDIR_OUT", "REDIR_OUT_APPEND", "REDIR_DEL_TWO", "REDIR_END"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_lex_read_modes(const t_lex_read_modes index)
{
	static const char	*label[LEN_LEX_RD_MDS] = {
		"CMB_ERR_LEX_RD_MD", "SYN_ERR_LEX_RD_MD", "CHR_ERR_LEX_RD_MD",
		"SPL_ERR_LEX_RD_MD", "DBL_ERR_LEX_RD_MD", "NEW_LEX_RD_MD",
		"STD_LEX_RD_MD", "SPL_LEX_RD_MD",
		"DBL_LEX_RD_MD", "ESCP_LEX_RD_MD", "PIPE_LEX_RD_MD", "AMP_LEX_RD_MD",
		"LT_LEX_RD_MD", "GT_LEX_RD_MD", "OR_LEX_RD_MD", "AND_LEX_RD_MD",
		"HDOC_LEX_RD_MD", "GGRT_LEX_RD_MD"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_pars_read_modes(const t_pars_read_modes index)
{
	static const char	*label[LEN_PARS_RD_MDS] = {
		"CMB_ERR_PARS_RD_MD", "SYN_ERR_PARS_RD_MD", "NEW_PARS_RD_MD",
		"STD_PARS_RD_MD", "SPL_PARS_RD_MD", "DBL_PARS_RD_MD", "ESCP_PARS_RD_MD",
		"PIPE_PARS_RD_MD", "AMP_PARS_RD_MD", "LT_PARS_RD_MD", "GT_PARS_RD_MD",
		"OR_PARS_RD_MD", "AND_PARS_RD_MD", "HDOC_PARS_RD_MD", "GGRT_PARS_RD_MD"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_exp_read_modes(const t_exp_read_modes index)
{
	static const char	*label[LEN_EXP_RD_MDS] = {
		"CMB_ERR_EXP_RD_MD", "NEW_EXP_RD_MD", "STD_EXP_RD_MD", "SPL_EXP_RD_MD",
		"DBL_EXP_RD_MD", "ESCP_EXP_RD_MD", "PIPE_EXP_RD_MD", "AMP_EXP_RD_MD",
		"LT_EXP_RD_MD", "GT_EXP_RD_MD", "OR_EXP_RD_MD", "AND_EXP_RD_MD",
		"HDOC_EXP_RD_MD", "GGRT_EXP_RD_MD", "DOL_EXP_RD_MD"
	};

	return ((char *)label[index]);
}

char	*ft_getlabel_redir_read_modes(const t_redir_read_modes index)
{
	static const char	*label[LEN_REDIR_RD_MDS] = {
		"ERR_REDIR_RD_MD", "NEW_REDIR_RD_MD", "STD_REDIR_RD_MD",
		"SPL_REDIR_RD_MD", "DBL_REDIR_RD_MD", "ESCP_REDIR_RD_MD",
		"PIPE_REDIR_RD_MD", "AMP_REDIR_RD_MD", "LT_REDIR_RD_MD",
		"GT_REDIR_RD_MD", "OR_REDIR_RD_MD", "AND_REDIR_RD_MD",
		"HDOC_REDIR_RD_MD", "GGRT_REDIR_RD_MD"
	};

	return ((char *)label[index]);
}
