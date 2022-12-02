/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:02:32 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 16:02:29 by lcalvie          ###   ########.fr       */
/*   Updated: 2022/12/02 15:51:44 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_prompt(t_shell *shell)
{
	t_lex		lex;
	t_pars		pars;
	char		*temp;

	ft_init_core(&lex, &pars, shell);
	if (!pars.there_hdoc)
		temp = lex.user_input;
	else
		lex.user_input = shell->retprompt;
	pars.r = ft_all_parsing_steps(&lex, &pars, shell);
	if (pars.r == 45)
		return (ft_error_ctrl_c(shell, &pars, &lex));
	if (!pars.there_hdoc)
	{
		free(temp);
		temp = NULL;
	}
	if (pars.r)
		return (pars.r);
	shell->hdoc_tab = pars.hdoc_tab;
	pars.cmd = pars.cmd_head;
	shell->cmd = pars.cmd;
	ft_pars_freeall(&pars);
	ft_tklist_freeall(&lex);
	return (0);
}

int	ft_error_ctrl_c(t_shell *shell, t_pars *pars, t_lex *lex)
{
	ft_redir_del_two(pars);
	ft_lstclear(&pars->cmd, del);
	ft_lstclear(&shell->cmd, del);
	ft_transformer(pars);
	ft_tklist_freeall(lex);
	//printf("token=%d\n", pars->nb_of_tokens);
	if (pars->command)
		ft_free_commandtokenlol(pars->command);
	ft_pars_freeall(pars);
	return (0);
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
	//printf("is heredoc ?? = %d\n", pars->there_hdoc);
	if (!pars->there_hdoc)
	{
		lex->user_input = ft_strdup(ft_initial_expansion(lex, pars));
		//printf("expansion : %s\n", lex->user_input);
		free(pars->token->id);
		pars->token->id = NULL;
		free(pars->token);
		pars->token = NULL;
	}
	return (0);
}

int	ft_all_parsing_steps(t_lex *lex, t_pars *pars, t_shell *shell)
{
	int	r;

	if (ft_around_lexer(lex) || ft_debug_content(lex, pars, "lex"))
		return (ft_error_return(lex, pars, shell));
	if (ft_around_parser(lex, pars)  || ft_debug_content(lex, pars, "pars"))
		return (ft_error_return(lex, pars, shell));
	pars->there_hdoc = 0;
	pars->lock_there_hdoc = 0;
	if (ft_expander(pars)  || ft_debug_content(lex, pars, "exp"))
		return (ft_error_return(lex, pars, shell));
	r = ft_around_redirector(lex, pars);
	if (r || ft_debug_content(lex, pars, "redir"))
	{
		if (r == 45)
			return (45);
		return (ft_error_return(lex, pars, shell));
	}
	if (ft_transformer(pars) || ft_debug_content(lex, pars, "trans"))
		return (ft_error_return(lex, pars, shell));
	return (0);
}
