/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:50:06 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 19:57:03 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_ctrl_c(t_shell *shell, t_pars *pars, t_lex *lex)
{
	ft_redir_del_two(pars);
	ft_lstclear(&pars->cmd, del);
	ft_lstclear(&shell->cmd, del);
	ft_transformer(pars);
	ft_tklist_freeall(lex);
	if (pars->command)
		ft_free_commandtokenlol(pars->command);
	ft_pars_freeall(pars);
	return (0);
}
