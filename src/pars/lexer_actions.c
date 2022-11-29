/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/28 19:51:01 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_lex_actions(t_lex *lex)
{
	lex->ft[LEX_NONE] = ft_lex_none;
	lex->ft[LEX_CATCH] = ft_lex_catch;
	lex->ft[LEX_KEEP] = ft_lex_keep;
	lex->ft[LEX_DROP] = ft_lex_drop;
	lex->ft[LEX_TAKE] = ft_lex_take;
	lex->ft[LEX_SKIP] = ft_lex_skip;
	lex->ft[LEX_REC] = ft_lex_record;
	lex->ft[LEX_END] = ft_lex_end;
	lex->ft[LEX_ERR] = ft_lex_err;
	return (0);
}

int	ft_check_forbidden_cmb(char *user_input)
{
	char 	*forbidden[] = { "&", NULL };
	int	i;

	i = 0;
	while(forbidden[i])
	{
		if (ft_strnstr(user_input, forbidden[i], ft_strlen(user_input)))
			return (1 + ERR_CD_CHR);
		i++;
	}
	return (0);
}

int	ft_lex_none(t_lex *lex)
{
	(void)lex;
	return (0);
}

int	ft_lex_catch(t_lex *lex)
{
	ft_lex_record(lex);
	lex->nb_taken_char = 0;
	if (lex->temp)
	{
		lex->token = ft_token_addnext(lex->token, ft_new_token(lex->temp));
		lex->nb_of_tokens++;
		lex->token->type = lex->prev_decision.token_type;
		free(lex->temp);
		lex->temp = NULL;
	}
	return (0);
}

int	ft_lex_keep(t_lex *lex)
{
	(void)lex;
	return (0);
}

int	ft_lex_drop(t_lex *lex)
{
	(void)lex;
	return (0);
}

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
		//ft_lex_take(lex);
		lex->prev_decision.token_type = lex->new_decision.token_type;
		ft_lex_catch(lex);
	}
	return (0);
}

int	ft_lex_err(t_lex *lex)
{
	return(1 + lex->new_decision.lex_read_mode);
}
