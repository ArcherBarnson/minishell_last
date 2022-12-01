/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:45:39 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_pars_actions(t_pars *pars)
{
	pars->ft_pars[PARS_NONE] = ft_pars_none;
	pars->ft_pars[PARS_NEW] = ft_pars_new;
	pars->ft_pars[PARS_CATCH] = ft_pars_catch;
	pars->ft_pars[PARS_KEEP] = ft_pars_keep;
	pars->ft_pars[PARS_DROP] = ft_pars_drop;
	pars->ft_pars[PARS_TAKE] = ft_pars_take;
	pars->ft_pars[PARS_SKIP] = ft_pars_skip;
	pars->ft_pars[PARS_END] = ft_pars_end;
	pars->ft_pars[PARS_ERR] = ft_pars_err;
	return (0);
}

int	ft_pars_none(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_pars_new(t_pars *pars)
{
	int	id;

	id = 0;
	if (pars->command)
	{
		pars->command->token = pars->command->token->next;
		id = pars->command->id;
	}
	pars->command = ft_command_addnext(pars->command,
			ft_new_command(pars->token));
	id++;
	pars->nb_of_commands++;
	pars->command->nb_of_tokens = 1;
	pars->command->id = id;
	pars->command->fd_in = 0;
	pars->command->fd_out = 1;
	return (0);
}

int	ft_pars_catch(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_pars_keep(t_pars *pars)
{
	(void)pars;
	return (0);
}
