/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:18:09 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 20:40:17 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_around_lexer(t_lex *lex)
{
	if (ft_lexer(lex))
	{
		ft_free_tokenlist(&(lex->token));
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

int	ft_lexer(t_lex *lex)
{
	int	ret;

	ret = 0;
	while (*lex->user_input && *lex->user_input != '\n' && ret == 0)
	{
		ret = ft_lex_apply_decision(lex);
		lex->user_input++;
	}
	if (!ret)
		ret = ft_lex_apply_decision(lex);
	if (lex->token)
		lex->token = lex->token->next;
	if (ret)
		return (ft_msgerr((char *)ft_getlabel_error_msgs_txt(ret - 1)));
	else
		return (0);
}

int	ft_around_parser(t_lex *lex, t_pars *pars)
{
	int	ret;

	pars->nb_of_commands = 0;
	pars->nb_of_tokens = lex->nb_of_tokens;
	ret = ft_parser(lex, pars);
	if (ret)
	{
		if (ret == 45)
			return (45);
		ft_tklist_freeall(lex);
		ft_pars_freeall(pars);
		return (1);
	}
	return (0);
}

int	ft_parser(t_lex *lex, t_pars *pars)
{
	ft_init_pars_counts(pars);
	pars->token = lex->token;
	pars->crt_tok_type = pars->token->type;
	while (pars->i++ < pars->nb_of_tokens && pars->r == 0)
	{
		pars->r = ft_pars_apply_decision(pars);
		pars->token = pars->token->next;
		pars->crt_tok_type = pars->token->type;
	}
	if (!pars->r)
	{
		pars->crt_tok_type = TOK_END_OF_INPUT;
		pars->r = ft_pars_apply_decision(pars);
	}
	if (pars->command)
	{
		pars->command->token = pars->command->token->next;
		pars->command = pars->command->next;
	}
	if (pars->r)
	{
		ft_msgerr((char *)ft_getlabel_error_msgs_txt(pars->r - 1));
		return (45);
	}
	return (0);
}

int	ft_around_redirector(t_lex *lex, t_pars *pars)
{
	int	r;

	r = ft_redirector(pars);
	if (r)
	{
		if (r == 45)
			return (45);
		(void)lex;
		return (1);
	}
	return (0);
}
