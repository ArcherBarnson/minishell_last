/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 04:43:20 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 14:38:17 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 130;
	return ;
}

void	sigquit_ignore(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	sigquit_cmd(int sig)
{
	(void)sig;
	exit(3);
}

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sigquit_cmd);
	return ;
}

void	display_signal_intercept(int sig)
{
	if (sig == SIG_INT)
		write(1, "\n", 1);
	if (sig == SIG_QUIT)
		write(1, "Quit (core dumped)\n", 19);
	if (sig == SIG_ABORT)
		write(1, "Aborted (core dumped)\n", 22);
	if (sig == BUS_ERR)
		write(1, "Bus error (core dumped)\n", 24);
	if (sig == SIG_SEGV)
		write(1, "Segmantation fault (core dumped)\n", 34);
	return ;
}
