/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_actions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:54:59 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 23:46:05 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_skip(t_shell *shell)
{
	shell->pars->nb_of_tokens--;
	shell->pars->token = shell->pars->token->next;
	return (0);
}

int	ft_redir_record(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ft_redir_in(t_shell *shell)
{
	int	ret;

	ret = 0;
	shell->pars->current_filename = shell->pars->command->token->next->id;
	if (ft_is_hdoc(shell->pars->current_filename, shell->pars))
		ft_change_hdoc_filename(shell->pars);
	ret = ft_open_infile(shell->pars, shell->pars->command->token->next->id);
	if (!ret && shell->pars->command->fd_in != -1)
	{
			shell->pars->command->fd_in = shell->pars->fd_in;
			shell->pars->mode0_fd_in = shell->pars->fd_in;
	}
	else
		shell->pars->command->fd_in = -1;
	return (0);
}

int	ft_redir_heredoc(t_shell *shell)
{
	int		ret;
	t_hdoc	*hdoc_current;

	ret = 0;
	if (shell->pars->prev_redir_decision.redir_read_mode == HDOC_REDIR_RD_MD)
	{
		//printf("consecutive heredocs\n");
		close(shell->pars->hdoc_list->fd);
		unlink(shell->pars->hdoc_list->file_name);
		hdoc_current = shell->pars->hdoc_list->prev;
		shell->pars->hdoc_list = ft_hdoc_list_freeone(shell->pars->hdoc_list);
		if (shell->pars->hdoc_list)
			shell->pars->hdoc_list = hdoc_current;
		shell->pars->hdoc_i--;
	}
	ret = ft_open_heredoc(shell, shell->pars->command->token->next->id);
	if (!ret && shell->pars->command)
	{
		shell->pars->command->fd_in = shell->pars->fd_in;
		shell->pars->mode1_fd_in = shell->pars->fd_in;
	}
	else
		shell->pars->command->fd_in = -1;
	return (ret);
}

int	ft_redir_out(t_shell *shell)
{
	int	ret;

	ret = 0;
	shell->pars->current_filename = shell->pars->command->token->next->id;
	if (ft_is_hdoc(shell->pars->current_filename, shell->pars))
		ft_change_hdoc_filename(shell->pars);
	ret = ft_open_outfile(shell->pars, shell->pars->command->token->next->id);
	if (!ret && shell->pars->command->fd_out != -1)
		shell->pars->command->fd_out = shell->pars->fd_out;
	else
		shell->pars->command->fd_out = -1;
	return (0);
}
