/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:33:55 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/21 13:20:32 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_cmd	*ft_read_prompt(char *user_input, t_hdoc_tab **hdoc_tab)
int	ft_read_prompt(t_shell *shell)
{
	t_lex		lex;
	t_pars		pars;

	ft_bzero(&lex, sizeof(t_lex));
	ft_bzero(&pars, sizeof(t_pars));
	ft_general_initialize(&lex, &pars);
	//lex.user_input = user_input;
	lex.user_input = shell->retprompt;
	//printf("check shell->retprompt : %s\n", lex.user_input);
	//printf("\n--------------------------\n");
	//printf("\033[0;32m%s\033[0m", lex.user_input);
	if (ft_around_lexer(&lex) || ft_print_debug_content(&lex, &pars, "lex"))
		return (ft_error_return(&lex, &pars, shell));
	if (ft_around_parser(&lex, &pars) || ft_print_debug_content(&lex, &pars, "pars"))
		return (ft_error_return(&lex, &pars, shell));
	if (ft_expander(&pars) || ft_print_debug_content(&lex, &pars, "exp"))
		ft_error_return(&lex, &pars, shell);
	if (ft_around_redirector(&lex, &pars) || ft_print_debug_content(&lex, &pars, "redir"))
		ft_error_return(&lex, &pars, shell);
	if (ft_transformer(&pars) || ft_print_debug_content(&lex, &pars, "trans"))
		ft_error_return(&lex, &pars, shell);
	//*hdoc_tab = pars.hdoc_tab;
	shell->hdoc_tab = pars.hdoc_tab;
	//printf("pars.cmd_head : %s\n", pars.cmd_head->token[0]);
	//printf("pars.cmd_head : %s\n", pars.cmd_head->cmd);
	pars.cmd = pars.cmd_head;
	shell->cmd = pars.cmd;
	ft_tklist_freeall(&lex);
	shell->pars = &pars;
	//ft_execfree_freeall(&pars);
	//ft_pars_freeall(&pars);
	return (0);
}

int	ft_error_return(t_lex *lex, t_pars *pars, t_shell *shell)
{
	(void)pars;
	shell->cmd = NULL;
	printf("return 1 to exec with shell->cmd = NULL\n");
	ft_tklist_freeall(lex);
//	ft_execfree_freeall(pars);
//	ft_pars_freeall(pars);
	return (1);
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
	int	ret;

	ret = ft_check_forbidden_cmb(lex->user_input);
	while (*lex->user_input && *lex->user_input != '\n'
		&& ret == 0)
	{
		ret = ft_lex_apply_decision(lex);
		lex->user_input++;
	}
	if (!ret)
		ret = ft_lex_apply_decision(lex);
	if (lex->token)
		lex->token = lex->token->next;
	if (ret)
		return (ft_msgerr((char *)ft_getlabel_error_msgs_txt
				(ret - 1)));
	else
		return (0);
}

int	ft_parser(t_lex *lex, t_pars *pars)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	pars->token = lex->token;
	pars->crt_tok_type = pars->token->type;
	while (i++ < pars->nb_of_tokens && ret == 0)
	{
		ret = ft_pars_apply_decision(pars);
		pars->token = pars->token->next;
		pars->crt_tok_type = pars->token->type;
	}
	if (!ret)
	{
		pars->crt_tok_type = TOK_END_OF_INPUT;
		ret = ft_pars_apply_decision(pars);
	}
	pars->command->token = pars->command->token->next;
	pars->command = pars->command->next;
	if (ret)
		return (ft_msgerr((char *)ft_getlabel_error_msgs_txt
				(ret - 1)));
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
