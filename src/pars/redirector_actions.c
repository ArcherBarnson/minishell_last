/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 17:30:18 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_redir_actions(t_shell *shell)
{
	shell->pars->ft_redir[REDIR_NONE] = ft_redir_none;
	shell->pars->ft_redir[REDIR_CATCH] = ft_redir_catch;
	shell->pars->ft_redir[REDIR_KEEP] = ft_redir_keep;
	shell->pars->ft_redir[REDIR_DROP] = ft_redir_drop;
	shell->pars->ft_redir[REDIR_SKIP] = ft_redir_skip;
	shell->pars->ft_redir[REDIR_IN] = ft_redir_in;
	shell->pars->ft_redir[REDIR_HDOC] = ft_redir_heredoc;
	shell->pars->ft_redir[REDIR_OUT] = ft_redir_out;
	shell->pars->ft_redir[REDIR_OUT_APPEND] = ft_redir_out_append;
	shell->pars->ft_redir[REDIR_DEL_TWO] = ft_redir_del_two;
	shell->pars->ft_redir[REDIR_END] = ft_redir_end;
	shell->pars->ft_redir[REDIR_ERR] = ft_redir_err;
	return (0);
}

int	ft_redir_none(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ft_redir_catch(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ft_redir_keep(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ft_redir_drop(t_shell *shell)
{
	(void)shell;
	return (0);
}
