/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_labels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:18:49 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:32:15 by mbourgeo         ###   ########.fr       */
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
