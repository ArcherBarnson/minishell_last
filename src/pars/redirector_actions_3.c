/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_actions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:55:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 15:47:35 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_out_append(t_pars *pars)
{
	int	ret;

	pars->current_filename = pars->command->token->next->id;
	if (ft_is_hdoc(pars->current_filename, pars))
		ft_change_hdoc_filename(pars);
	ret = 0;
	ret = ft_open_append_outfile(pars, pars->command->token->next->id);
	if (!ret)
		pars->command->fd_out = pars->fd_out;
	else
		pars->command->fd_out = -1;
	return (ret);
}

int	ft_redir_del_two(t_pars *pars)
{
	pars->token = ft_free_one_token(pars->token);
	pars->command->nb_of_tokens--;
	pars->token = ft_free_one_token(pars->token);
	pars->command->nb_of_tokens--;
	pars->redir = 1;
	if (pars->command->nb_of_tokens != 0)
		pars->token = pars->token->prev;
	pars->command->token = pars->token;
	return (0);
}

int	ft_redir_end(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_err(t_pars *pars)
{
	return (1 + pars->new_redir_decision.redir_read_mode);
}
