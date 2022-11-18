/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:33:55 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/24 11:46:43 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_read_prompt(char *user_input, t_hdoc_tab **hdoc_tab)
{
	t_lex		lex;
	t_pars		pars;

	ft_bzero(&lex, sizeof(t_lex));
	ft_bzero(&pars, sizeof(t_pars));
	ft_general_initialize(&lex, &pars);
	lex.user_input = user_input;
	printf("\n--------------------------\n");
	printf("\033[0;32m%s\033[0m", lex.user_input);
	if (ft_around_lexer(&lex) || ft_print_debug_content(&lex, &pars, "lex"))
		return (NULL);
	if (ft_around_parser(&lex, &pars) || ft_print_debug_content(&lex, &pars, "pars"))
		return (NULL);
	if (ft_expander(&pars) || ft_print_debug_content(&lex, &pars, "exp"))
		return (NULL);
	if (ft_around_redirector(&lex, &pars) || ft_print_debug_content(&lex, &pars, "redir"))
		return (NULL);
	if (ft_transformer(&pars) || ft_print_debug_content(&lex, &pars, "trans"))
		return (NULL);
	*hdoc_tab = pars.hdoc_tab;
	pars.cmd = pars.cmd_head;
	ft_tklist_freeall(&lex);
	//test
	//ft_execfree_freeall(&pars);
	//ft_pars_freeall(&pars);
	return (pars.cmd);
}

int	ft_around_lexer(t_lex *lex)
{
	if (ft_lexer(lex))
	{
		ft_free_tokenlist(lex->token);
		lex->token = NULL;
		lex->temp = ft_strndup("", 0);
		lex->token = ft_token_addnext(lex->token, ft_new_token(lex->temp));
		lex->nb_of_tokens = 1;
		lex->token->type = lex->new_decision.token_type;
		free(lex->temp);
		lex->temp = NULL;
		return (1);
	}
	return (0);
}

int	ft_around_parser(t_lex *lex, t_pars *pars)
{
	pars->nb_of_commands = 0;
	pars->nb_of_tokens = lex->nb_of_tokens;
	if (ft_parser(lex, pars))
	{
		ft_tklist_freeall(lex);
		ft_pars_freeall(pars);
		return (1);
	}
	return (0);
}

int	ft_around_redirector(t_lex *lex, t_pars *pars)
{
	if (ft_redirector(pars))
	{
		ft_tklist_freeall(lex);
		ft_pars_freeall(pars);
		return (1);
	}
	return (0);
}

int	ft_lexer(t_lex *lex)
{
	while (*lex->user_input && *lex->user_input != '\n'
		&& lex->prev_decision.lex_read_mode != ERR_LEX_RD_MD)
	{
		if (ft_lex_apply_decision(lex))
			return (1);
		lex->user_input++;
	}
	if (lex->new_decision.lex_read_mode != ERR_LEX_RD_MD)
	{
		if (ft_lex_apply_decision(lex))
			return (1);
	}
	if (lex->new_decision.lex_read_mode == ERR_LEX_RD_MD)
		return (ft_msgerr((char *)ft_getlabel_error_msgs
				(lex->new_decision.token_type - TOK_ERR_MARK - 1)));
	if (lex->new_decision.lex_read_mode != ERR_LEX_RD_MD)
		lex->token = lex->token->next;
	return (0);
}

int	ft_parser(t_lex *lex, t_pars *pars)
{
	int	i;

	i = 0;
	pars->token = lex->token;
	while (i++ < pars->nb_of_tokens)
	{
		if (ft_pars_apply_decision(pars))
			return (1);
		pars->token = pars->token->next;
	}
	pars->command->token = pars->command->token->next;
	pars->command = pars->command->next;
	//ft_print_parser_content(pars);
	return (0);
}

int	ft_expander(t_pars *pars)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (i++ < pars->nb_of_commands)
	{
		while (j++ < pars->command->nb_of_tokens)
		{
			pars->token = pars->command->token;
			ft_init_expander(pars);
			pars->before_dol_mode = 0;
			pars->parser_text = ft_strndup(pars->token->id, 0);
			temp = pars->parser_text;
			ft_inner_loop_expander(pars);
			free(temp);
			pars->command->token = pars->command->token->next;
			ft_init_expander(pars);
		}
		pars->command = pars->command->next;
		j = 0;
	}
	return (0);
}

int	ft_inner_loop_expander(t_pars *pars)
{
	while (1)
	{
		//printf("checking token->type : %d\n", pars->token->type);
		if (pars->token->type == TOK_WORD)
			ft_exp_apply_decision(pars);
		if (pars->parser_text[0] == '\0')
			break ;
		pars->parser_text++;
		pars->offset_start++;
	}
	return (0);
}

int	ft_redirector(t_pars *pars)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	ft_init_redir_decisions(pars);
	ft_init_redir_actions(pars);
	while (i++ < pars->nb_of_commands)
	{
		k = pars->command->nb_of_tokens;
		while (j++ < k)
		{
			pars->token = pars->command->token;
			if (ft_redir_apply_decision(pars))
				return (1);
			pars->command->token = pars->command->token->next;
		}
		pars->command = pars->command->next;
		count += pars->command->nb_of_tokens;
		j = 0;
	}
	return (0);
}

int	ft_transformer(t_pars *pars)
{
	int		i;

	i = 0;
	while (i++ < pars->nb_of_commands)
	{
		pars->cmd = ft_cmd_addnext(pars->cmd,
				ft_new_cmd(ft_token_list_to_tab(pars->command)));
		if (i == 1)
			pars->cmd_head = pars->cmd;
		pars->cmd->id = pars->command->id;
		pars->cmd->nb_of_tokens = pars->command->nb_of_tokens;
		pars->cmd->fd_in = pars->command->fd_in;
		pars->cmd->fd_out = pars->command->fd_out;
		pars->command = pars->command->next;
	}
	pars->hdoc_tab = ft_hdoc_list_to_tab(pars->hdoc_list,
			ft_count_list(pars->hdoc_list));
	pars->cmd = pars->cmd_head;
	return (0);
}
