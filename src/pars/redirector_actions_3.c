/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_actions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:55:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 19:20:28 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_out_append(t_shell *shell)
{
	int	ret;

	shell->pars->current_filename = shell->pars->command->token->next->id;
	if (ft_is_hdoc(shell->pars->current_filename, shell->pars))
		ft_change_hdoc_filename(shell->pars);
	ret = 0;
	ret = ft_open_append_outfile(shell->pars,
			shell->pars->command->token->next->id);
	if (!ret)
		shell->pars->command->fd_out = shell->pars->fd_out;
	else
		shell->pars->command->fd_out = -1;
	return (ret);
}

int	ft_redir_del_two(t_shell *shell)
{
	shell->pars->token = ft_free_one_token(shell->pars->token);
	shell->pars->command->nb_of_tokens--;
	shell->pars->token = ft_free_one_token(shell->pars->token);
	shell->pars->command->nb_of_tokens--;
	shell->pars->redir = 1;
	if (shell->pars->command->nb_of_tokens != 0)
		shell->pars->token = shell->pars->token->prev;
	shell->pars->command->token = shell->pars->token;
	return (0);
}

int	ft_redir_end(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ft_redir_err(t_shell *shell)
{
	return (1 + shell->pars->new_redir_decision.redir_read_mode);
}
