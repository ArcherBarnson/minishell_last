/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:02:32 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 21:45:52 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_read_prompt(t_shell *shell)
{
	t_lex		lex;
	t_pars		pars;
	char		*temp;
	int			ret;

	ft_init_core(&lex, &pars, shell);
	pars.r = 0;
	if (!pars.there_hdoc)
		temp = lex.user_input;
	else
		lex.user_input = shell->retprompt;
	ret = ft_all_parsing_steps(&lex, &pars, shell);
	if (!pars.there_hdoc)
	{
		free(temp);
		temp = NULL;
	}
	if (ret)
		return (ret);
	shell->hdoc_tab = pars.hdoc_tab;
	pars.cmd = pars.cmd_head;
	shell->cmd = pars.cmd;
<<<<<<< Updated upstream
	//printf("last_infile_mode = %d\n", pars.last_infile_mode);
=======
>>>>>>> Stashed changes
	ft_tklist_freeall(&lex);
	ft_pars_freeall(&pars);
	return (0);
}

int	ft_there_hdoc(t_pars *pars, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '<')
		i++;
	if (str[i] == '<' && str[i + 1] == '<')
	{
		pars->there_hdoc = 1;
		return (1);
	}
	return (0);
}

int	ft_init_core(t_lex *lex, t_pars *pars, t_shell *shell)
{
	ft_bzero(lex, sizeof(t_lex));
	ft_bzero(pars, sizeof(t_pars));
	shell->lex = lex;
	shell->pars = pars;
	ft_general_initialize(lex, pars, shell);
	pars->there_hdoc = 0;
	lex->user_input_raw = shell->retprompt;
	pars->ms_env = shell->ms_env;
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
	if (ft_around_lexer(lex)) // || ft_debug_content(lex, pars, "lex"))
		return (ft_error_return(lex, pars, shell));
	if (ft_around_parser(lex, pars)) // || ft_debug_content(lex, pars, "pars"))
		return (ft_error_return(lex, pars, shell));
	pars->there_hdoc = 0;
	pars->lock_there_hdoc = 0;
	if (ft_expander(pars)) // || ft_debug_content(lex, pars, "exp"))
		return (ft_error_return(lex, pars, shell));
	if (ft_around_redirector(lex, pars, shell))
		// || ft_debug_content(lex, pars, "redir"))
		return (ft_error_return(lex, pars, shell));
	if (ft_transformer(pars)) // || ft_debug_content(lex, pars, "trans"))
		return (ft_error_return(lex, pars, shell));
	return (0);
}

int	ft_error_return(t_lex *lex, t_pars *pars, t_shell *shell)
{
	(void)pars;
	shell->cmd = NULL;
	ft_tklist_freeall(lex);
	return (1);
}
