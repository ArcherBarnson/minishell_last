/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:42:57 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:43:10 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lex_take(t_lex *lex)
{
	lex->nb_taken_char++;
	return (0);
}

int	ft_lex_skip(t_lex *lex)
{
	(void)lex;
	return (0);
}

int	ft_lex_record(t_lex *lex)
{
	char	*temp1;
	char	*temp2;

	if (lex->nb_taken_char)
	{
		if (!lex->temp)
		{
			lex->temp = malloc(sizeof(char));
			ft_bzero(lex->temp, sizeof(char));
			temp1 = lex->temp;
		}
		else
		{
			temp1 = ft_strndup(lex->temp, 0);
			free(lex->temp);
		}
		temp2 = ft_substr(lex->user_input - lex->nb_taken_char,
				0, lex->nb_taken_char);
		lex->temp = ft_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
		lex->nb_taken_char = 0;
	}
	return (0);
}

int	ft_lex_end(t_lex *lex)
{
	if (!lex->token)
	{
		lex->temp = ft_strdup("");
		ft_lex_catch(lex);
	}
	else
	{
		lex->prev_decision.token_type = lex->new_decision.token_type;
		ft_lex_catch(lex);
	}
	return (0);
}

int	ft_lex_err(t_lex *lex)
{
	return (1 + lex->new_decision.lex_read_mode);
}
