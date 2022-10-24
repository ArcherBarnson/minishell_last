/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_apply_decision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/11 23:25:25 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lex_apply_decision(t_lex *lex)
{
	if (ft_char_type(lex->user_input[0]) == ERR_CHAR)
		return (ft_msgerr(ERR_NOT_HANDLED), 1);
	lex->prev_decision = lex->new_decision;
	lex->new_decision = lex->decision[lex->prev_decision.lex_read_mode]
	[ft_char_type(lex->user_input[0])];
	ft_print_debug_lex(lex);
	if (lex->new_decision.buffer_action == LEX_ERR)
		return (ft_msgerr(ERR_CASE), 1);
	if (lex->ft[lex->new_decision.buffer_action](lex))
		return (1);
	lex->ft[lex->new_decision.char_action](lex);
	return (0);
}
