/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:33:35 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:30:08 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*free_heredoc(t_shell *shell, int mode)
{
	static t_shell	*save_shell;

	if (mode == 0)
		save_shell = shell;
	return (save_shell);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	ft_transformer(free_heredoc(NULL, 1)->pars);
	ft_tklist_freeall(free_heredoc(NULL, 1)->lex);
	ft_pars_freeall(free_heredoc(NULL, 1)->pars);
	ft_lstclear(&free_heredoc(NULL, 1)->pars->cmd, del);
	free_all(free_heredoc(NULL, 1));
	exit(130);
}

int	ft_free_commandtoken(t_pars *pars)
{
	t_command	*temp;

	while (1)
	{
		temp = pars->command;
		pars->command = ft_command_jumpcurrent(pars->command->prev,
				pars->command->next);
		ft_free_tokenlist(&(temp->token));
		if (pars->command == temp)
		{
			pars->command = NULL;
			break ;
		}
		temp = NULL;
	}
	pars->command = NULL;
	return (0);
}

t_hdoc	*ft_hdoc_addnext(t_hdoc *current, t_hdoc *next)
{
	if (!current)
		return (current = next, current);
	else if (!next)
		return (ft_msgerr(ERR_NULLHDOC), NULL);
	else
	{
		next->prev = current;
		next->next = current->next;
		current->next->prev = next;
		current->next = next;
	}
	return (next);
}

t_hdoc	*ft_hdoc_jumpcurrent(t_hdoc *prev, t_hdoc *next)
{
	if (next->next != next)
	{
		prev->next = next;
		next->prev = prev;
	}
	return (next);
}
