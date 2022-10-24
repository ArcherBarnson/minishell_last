/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 08:52:39 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_flag(void)
{
	printf("\033[37;1mHello World!\033[0m\n");
}

int	ft_print_debug_content(t_lex *lex, t_pars *pars, char *choice)
{
	if (ft_strcmp(choice, "lex"))
		ft_print_lexer_content(lex);
	else if (ft_strcmp(choice, "pars"))
		ft_print_parser_content(pars);
	else if (ft_strcmp(choice, "exp"))
		ft_print_expander_content(pars);
	else if (ft_strcmp(choice, "redir"))
		ft_print_redirector_content(pars);
	else if (ft_strcmp(choice, "trans"))
		ft_print_transformer_content(pars->cmd);
	return (0);
}

int	ft_print_debug_lex(t_lex *lex)
{
	printf("\033[33;2m");
	if (lex->new_decision.buffer_action == LEX_ERR)
	{
		printf("\033[31;2m\n<- ERROR in LEXER -> \n\033[0m");
		printf("[1] : %s\n", ft_getlabel_lex_read_modes
			(lex->prev_decision.lex_read_mode));
		printf("[2] : %s\n", ft_getlabel_char_types
			(ft_char_type(lex->user_input[0])));
	}
	printf("\033[33;2m");
	printf("\033[0m");
	return (0);
}

int	ft_print_debug_pars(t_pars *pars)
{
	printf("\033[33;2m");
	if (pars->new_pars_decision.token_action == PARS_ERR)
	{
		printf("\033[31;2m\n<- ERROR in PARSER -> \n\033[0m");
		printf("[1] : %s\n", ft_getlabel_pars_read_modes
			(pars->prev_pars_decision.pars_read_mode));
		printf("[2] : %s\n", ft_getlabel_token_types(pars->token->type));
	}
	printf("\033[33;2m");
	printf("\033[0m");
	return (0);
}

int	ft_print_debug_exp(t_pars *pars)
{
	printf("\033[33;2m");
	if (pars->new_exp_decision.buffer_action == EXP_ERR)
	{
		printf("\033[31;2m\n<- ERROR in EXPANDER -> \n\033[0m");
		printf("[1] : %s\n", ft_getlabel_exp_read_modes
			(pars->prev_exp_decision.exp_read_mode));
		//printf("char : %c\n", pars->parser_text[0]);
		printf("[2] : %s\n", ft_getlabel_char_types
			(ft_char_type(pars->parser_text[0])));
	}
	printf("\033[33;2m");
	printf("\033[0m");
	return (0);
}

int	ft_print_debug_redir(t_pars *pars)
{
	printf("\033[33;2m");
	if (pars->new_redir_decision.token_action == REDIR_ERR)
	{
		printf("\033[31;2m\n<- ERROR in REDIRECTOR -> \n\033[0m");
		printf("[1] : %s\n", ft_getlabel_redir_read_modes
			(pars->prev_redir_decision.redir_read_mode));
		printf("[2] : %s\n", ft_getlabel_token_types(pars->token->type));
	}
	printf("\033[33;2m");
	printf("\033[0m");
	return (0);
}

int	ft_print_debug_cmd_content(t_pars *pars)
{
	int	i;

	printf("\033[33;2m");
	pars->cmd = pars->cmd_head;
	printf("\nCHECK CMD CONTENT\n");
	while (pars->cmd)
	{
		i = 0;
		printf("command id : %d\n", pars->cmd->id);
		while (pars->cmd->token[i++])
			printf("   token[%d] : <%s>\n", i - 1, pars->cmd->token[i - 1]);
		pars->cmd = pars->cmd->next;
	}
	pars->cmd = pars->cmd_head;
	printf("\033[0m");
	return (0);
}

int	ft_print_lexer_content(t_lex *lex)
{
	int	i;

	i = 0;
	printf("\nLEXER CONTENT\n");
	while (i++ < lex->nb_of_tokens)
	{
		printf("%s <%s>\n", lex->token->id,
			ft_getlabel_token_types(lex->token->type));
		lex->token = lex->token->next;
	}
	printf("\033[0m");
	printf("\n");
	return (0);
}

int	ft_print_parser_content(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\nPARSER CONTENT\n");
	while (i++ < pars->nb_of_commands)
	{
		printf("------> starting command id <%d>\n", pars->command->id);
		while (j++ < pars->command->nb_of_tokens)
		{
			printf("%s <%s>\n", pars->command->token->id,
				ft_getlabel_token_types(pars->command->token->type));
			pars->command->token = pars->command->token->next;
		}
		pars->command = pars->command->next;
		j = 0;
	}
	printf("\033[0m");
	printf("\n");
	return (0);
}

int	ft_print_expander_content(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\nEXPANDER CONTENT\n");
	while (i++ < pars->nb_of_commands)
	{
		printf("------> starting command id <\033[0m%d\033[0m>\n", pars->command->id);
		while (j++ < pars->command->nb_of_tokens)
		{
			printf("\033[0m%s \033[0m<%s>\n", pars->command->token->id,
				ft_getlabel_token_types(pars->command->token->type));
			pars->command->token = pars->command->token->next;
		}
		pars->command = pars->command->next;
		j = 0;
	}
	printf("\n");
	return (0);
}

int	ft_print_redirector_content(t_pars *pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("\nREDIRECTOR CONTENT\n");
	while (i++ < pars->nb_of_commands)
	{
		printf("------> starting command id <\033[0;31m%d\033[0m> <in \033[0;32m%d\033[0m> <out \033[0;32m%d\033[0m>\n", pars->command->id,
			pars->command->fd_in, pars->command->fd_out);
		while (j++ < pars->command->nb_of_tokens)
		{
			printf("\033[0;31m%s \033[0m<%s>\n", pars->command->token->id,
				ft_getlabel_token_types(pars->command->token->type));
			pars->command->token = pars->command->token->next;
		}
		pars->command = pars->command->next;
		j = 0;
	}
	printf("\033[0m");
	printf("\n");
	return (0);
}

int	ft_print_transformer_content(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("\nTRANSFORMER CONTENT\n");
	while (cmd)
	{
		printf("------> starting command id <\033[0;31m%d\033[0m> <in \033[0;32m%d\033[0m> <out \033[0;32m%d\033[0m>\n", cmd->id,
			cmd->fd_in, cmd->fd_out);
		while (i++ < cmd->nb_of_tokens)
		{
			printf("\033[0;31m%s\033[0m\n", cmd->token[i - 1]);
		}
		cmd = cmd->next;
		i = 0;
	}
	printf("\033[0m");
	printf("\n");
	return (0);
}
