/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:10:26 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 10:10:36 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_return(t_lex *lex, t_pars *pars, t_shell *shell)
{
	(void)pars;
	shell->cmd = NULL;
	ft_tklist_freeall(lex);
	return (1);
}
