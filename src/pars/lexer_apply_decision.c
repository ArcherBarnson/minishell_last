/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_apply_decision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:50:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/25 15:15:46 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lex_apply_decision(t_lex *lex)
{
	//printf("current char in lex : %c\n", lex->user_input[0]);
	// remove those debug lines
	//if (ft_char_type(lex->user_input[0]) == END_CHAR)
	//	printf("next char is END_CHAR\n");
	//
	//if (ft_char_type(lex->user_input[0]) == ERR_CHAR)
	//	printf("%s\n", ERR_NOT_HANDLED);
	lex->prev_decision = lex->new_decision;
	lex->new_decision = lex->decision[lex->prev_decision.lex_read_mode]
	[ft_char_type(lex->user_input[0])];
	// debug to handle case where combination of characheters is unknown
	//ft_print_debug_lex(lex);
	lex->ft[lex->new_decision.buffer_action](lex);
	// handle now each error cases
	//if (ft_char_type(lex->user_input[0]) == ERR_CHAR)
	//	return (1);
	//if (lex->new_decision.buffer_action == LEX_ERR)
	//	return (1);
	// if no error detected then apply actions (buffer and char)
	//printf("new mode is : %s\n", ft_getlabel_lex_read_modes(lex->new_decision.lex_read_mode));
	//printf("back from action \n");
	return (lex->ft[lex->new_decision.char_action](lex));
}
