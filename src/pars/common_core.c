/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:02:32 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 20:45:05 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_end_read_prompt(t_shell *shell, t_pars *pars, char *temp, t_lex *lex)
{
	if (pars->r == 44)
	{
		ft_lstclear(&pars->cmd, del);
		ft_lstclear(&shell->cmd, del);
		if (pars->command)
			ft_free_commandtokenlol(pars->command);
		ft_pars_freeall(pars);
	}
	if (!pars->there_hdoc)
	{
		free(temp);
		temp = NULL;
	}
	if (pars->r)
		return (pars->r);
	shell->hdoc_tab = pars->hdoc_tab;
	pars->cmd = pars->cmd_head;
	shell->cmd = pars->cmd;
	ft_pars_freeall(pars);
	ft_tklist_freeall(lex);
	return (0);
}

int	ft_read_prompt(t_shell *shell)
{
	t_lex		lex;
	t_pars		pars;
	char		*temp;

	temp = NULL;
	ft_init_core(&lex, &pars, shell);
	if (!pars.there_hdoc)
		temp = lex.user_input;
	else
		lex.user_input = shell->retprompt;
	pars.r = ft_all_parsing_steps(&lex, &pars, shell);
	if (pars.temp)
		free(pars.temp);
	if (pars.r == 45)
	{
		shell->hdv = 45;
		return (ft_error_ctrl_c(shell, &pars, &lex));
	}
	return (ft_end_read_prompt(shell, &pars, temp, &lex));
}

int	ft_there_hdoc(t_pars *pars, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				pars->there_hdoc = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_init_core(t_lex *lex, t_pars *pars, t_shell *shell)
{
	ft_bzero(lex, sizeof(t_lex));
	ft_bzero(pars, sizeof(t_pars));
	shell->lex = lex;
	shell->pars = pars;
	ft_general_initialize(lex, pars);
	pars->there_hdoc = 0;
	lex->user_input_raw = shell->retprompt;
	pars->ms_env = shell->ms_env;
	ft_there_hdoc(pars, lex->user_input_raw);
	if (!pars->there_hdoc)
	{
		lex->user_input = ft_strdup(ft_initial_expansion(lex, pars));
		free(pars->token->id);
		pars->token->id = NULL;
		free(pars->token);
		pars->token = NULL;
	}
	return (0);
}

int	ft_all_parsing_steps(t_lex *lex, t_pars *pars, t_shell *shell)
{
	int	r0;

	if (ft_around_lexer(lex))
		return (ft_error_return(lex, pars, shell));
	r0 = ft_around_parser(lex, pars);
	if (r0)
	{
		if (r0 == 45)
			return (44);
		return (ft_error_return(lex, pars, shell));
	}
	pars->there_hdoc = 0;
	pars->lock_there_hdoc = 0;
	if (ft_expander(pars))
		return (ft_error_return(lex, pars, shell));
	pars->r = ft_around_redirector(lex, pars);
	if (pars->r)
	{
		if (pars->r == 45)
			return (45);
		return (ft_error_return(lex, pars, shell));
	}
	if (ft_transformer(pars))
		return (ft_error_return(lex, pars, shell));
	return (0);
}
