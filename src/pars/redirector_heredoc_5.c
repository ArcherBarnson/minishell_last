/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:33:35 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 23:33:47 by mbourgeo         ###   ########.fr       */
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
	write(0, "\0", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// reste des leaks ???? 
	free_all(free_heredoc(NULL, 1));
	exit(130);
	return ;
}
