/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_labels_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:32:19 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:32:39 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
