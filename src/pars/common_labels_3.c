/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_labels_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:32:57 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:32:59 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
