/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_apply_decision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/29 21:44:58 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lex_apply_decision(t_lex *lex)
{
	lex->prev_decision = lex->new_decision;
	lex->new_decision = lex->decision[lex->prev_decision.lex_read_mode]
	[ft_char_type(lex->user_input[0])];
	ft_print_debug_lex(lex);
	lex->ft[lex->new_decision.buffer_action](lex);
	return (lex->ft[lex->new_decision.char_action](lex));
}
