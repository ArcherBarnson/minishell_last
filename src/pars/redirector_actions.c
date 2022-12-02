/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:53:21 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_redir_actions(t_pars *pars)
{
	pars->ft_redir[REDIR_NONE] = ft_redir_none;
	pars->ft_redir[REDIR_CATCH] = ft_redir_catch;
	pars->ft_redir[REDIR_KEEP] = ft_redir_keep;
	pars->ft_redir[REDIR_DROP] = ft_redir_drop;
	pars->ft_redir[REDIR_SKIP] = ft_redir_skip;
	pars->ft_redir[REDIR_IN] = ft_redir_in;
	pars->ft_redir[REDIR_HDOC] = ft_redir_heredoc;
	pars->ft_redir[REDIR_OUT] = ft_redir_out;
	pars->ft_redir[REDIR_OUT_APPEND] = ft_redir_out_append;
	pars->ft_redir[REDIR_DEL_TWO] = ft_redir_del_two;
	pars->ft_redir[REDIR_END] = ft_redir_end;
	pars->ft_redir[REDIR_ERR] = ft_redir_err;
	return (0);
}

int	ft_redir_none(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_catch(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_keep(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_drop(t_pars *pars)
{
	(void)pars;
	return (0);
}
