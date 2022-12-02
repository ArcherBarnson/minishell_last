/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:33:35 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 04:06:00 by mbourgeo         ###   ########.fr       */
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
	//free(free_heredoc(NULL, 1)->pars->str_gnl);
	ft_transformer(free_heredoc(NULL, 1)->pars);
	ft_tklist_freeall(free_heredoc(NULL, 1)->lex);
	ft_pars_freeall(free_heredoc(NULL, 1)->pars);
	ft_lstclear(&free_heredoc(NULL, 1)->pars->cmd, del);
	free_all(free_heredoc(NULL, 1));
	//free(pars->token->id);
	//ft_pars_freeall(pars);
	exit(130);
}
