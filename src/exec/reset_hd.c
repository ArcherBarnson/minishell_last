/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:47:09 by jtaravel          #+#    #+#             */
/*   Updated: 2022/12/06 12:47:48 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_hd(t_shell *shell)
{
	if (shell->hdv != 45)
	{
		ft_unlink_allhdoc(shell->hdoc_tab);
		ft_free_hdoctab(shell->hdoc_tab);
		shell->hdv = 0;
	}
	else if (g_exit_code != 130)
	{
		ft_unlink_allhdoc(shell->hdoc_tab);
		ft_free_hdoctab(shell->hdoc_tab);
	}
}
