/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_actions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:54:59 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 20:05:21 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_skip(t_pars *pars)
{
	pars->nb_of_tokens--;
	pars->token = pars->token->next;
	return (0);
}

int	ft_redir_record(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_in(t_pars *pars)
{
	int	ret;

	ret = 0;
	pars->current_filename = pars->command->token->next->id;
	if (ft_is_hdoc(pars->current_filename, pars))
		ft_change_hdoc_filename(pars);
	ret = ft_open_infile(pars, pars->command->token->next->id);
	if (!ret && pars->command->fd_in != -1)
	{
		pars->command->fd_in = pars->fd_in;
		pars->mode0_fd_in = pars->fd_in;
	}
	else
	{
		pars->command->fd_in = -1;
		pars->mode0_fd_in = -1;
	}
	return (0);
}

int	ft_redir_heredoc(t_pars *pars)
{
	t_hdoc	*hdoc_current;

	pars->ret = 0;
	if (pars->prev_redir_decision.redir_read_mode == HDOC_REDIR_RD_MD)
	{
		close(pars->hdoc_list->fd);
		unlink(pars->hdoc_list->file_name);
		hdoc_current = pars->hdoc_list->prev;
		pars->hdoc_list = ft_hdoc_list_freeone(pars->hdoc_list);
		if (pars->hdoc_list)
			pars->hdoc_list = hdoc_current;
		pars->hdoc_i--;
	}
	pars->ret = ft_open_heredoc(pars, pars->command->token->next->id);
	if (!pars->ret && pars->command->fd_in != -1)
	{
		pars->command->fd_in = pars->fd_in;
		pars->mode1_fd_in = pars->fd_in;
	}
	else
	{
		pars->command->fd_in = -1;
		pars->mode1_fd_in = -1;
	}
	return (pars->ret);
}

int	ft_redir_out(t_pars *pars)
{
	int	ret;

	ret = 0;
	pars->current_filename = pars->command->token->next->id;
	if (ft_is_hdoc(pars->current_filename, pars))
		ft_change_hdoc_filename(pars);
	ret = ft_open_outfile(pars, pars->command->token->next->id);
	if (!ret && pars->command->fd_out != -1)
		pars->command->fd_out = pars->fd_out;
	else
		pars->command->fd_out = -1;
	return (0);
}
