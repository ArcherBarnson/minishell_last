/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:19:52 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:58:31 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirector(t_pars *pars)
{
	ft_init_pars_counts(pars);
	ft_init_redir_decisions(pars);
	ft_init_redir_actions(pars);
	while (pars->i++ < pars->nb_of_commands)
	{
		pars->k = pars->command->nb_of_tokens;
		pars->fd_out = 1;
		while (pars->j++ < pars->k)
		{
			pars->token = pars->command->token;
			pars->r = ft_redir_apply_decision(pars);
			if (pars->r == 45)
				return (45);
			if (pars->redir && pars->j++)
				pars->redir = 0;
			if (pars->r)
				return (pars->r);
			ft_finilize_fd_in(pars);
		}
		pars->command = pars->command->next;
		pars->count += pars->command->nb_of_tokens;
		pars->j = 0;
	}
	return (0);
}

int	ft_finilize_fd_in(t_pars *pars)
{
	if (pars->fd_in && pars->last_infile_mode == 0)
		pars->command->fd_in = pars->mode0_fd_in;
	else if (pars->fd_in && pars->last_infile_mode == 1)
	{
		pars->command->fd_in = pars->mode1_fd_in;
		if (pars->mode0_fd_in)
			close (pars->mode0_fd_in);
	}
	if (pars->command->nb_of_tokens)
		pars->command->token = pars->command->token->next;
	pars->fd_in = 0;
	return (0);
}

int	ft_expander(t_pars *pars)
{
	char	*temp;

	ft_init_pars_counts(pars);
	while (pars->i++ < pars->nb_of_commands)
	{
		while (pars->j++ < pars->command->nb_of_tokens)
		{
			pars->token = pars->command->token;
			ft_init_expander(pars);
			pars->before_dol_mode = 0;
			pars->parser_text = ft_strdup(pars->token->id);
			temp = pars->parser_text;
			pars->r = ft_inner_loop_expander(pars);
			free(temp);
			if (pars->r)
				return (pars->r);
			pars->command->token = pars->command->token->next;
			ft_init_expander(pars);
		}
		pars->command = pars->command->next;
		pars->j = 0;
	}
	return (0);
}

int	ft_inner_loop_expander(t_pars *pars)
{
	int	ret;

	ret = 0;
	while (1)
	{
		if (pars->token->type == TOK_HDOC)
		{
			pars->lock_there_hdoc = 1;
			pars->there_hdoc = 1;
		}
		else if (!pars->lock_there_hdoc)
			pars->there_hdoc = 0;
		else
			pars->lock_there_hdoc = 0;
		if (pars->token->type == TOK_WORD)
			ret = ft_exp_apply_decision(pars);
		if (pars->parser_text[0] == '\0' || pars->parser_text[0] == '\n')
			break ;
		pars->parser_text++;
		pars->offset_start++;
	}
	if (ret)
		return (ft_msgerr((char *)ft_getlabel_error_msgs_txt
				(ret - 1)));
	return (0);
}

int	ft_transformer(t_pars *pars)
{
	int			i;

	i = 0;
	while (i++ < pars->nb_of_commands)
	{
		if (pars->command->nb_of_tokens && !(pars->ret_45))
		{
			pars->cmd = ft_cmd_addnext(pars->cmd,
					ft_new_cmd(ft_token_list_to_tab(pars->command)));
			if (i == 1)
				pars->cmd_head = pars->cmd;
			pars->cmd->id = pars->command->id;
			pars->cmd->nb_of_tokens = pars->command->nb_of_tokens;
			pars->cmd->fd_in = pars->command->fd_in;
			pars->cmd->fd_out = pars->command->fd_out;
		}
		pars->command = pars->command->next;
	}
	pars->hdoc_tab = ft_hdoc_list_to_tab(pars->hdoc_list,
			ft_count_list(pars->hdoc_list));
	pars->cmd = pars->cmd_head;
	return (0);
}
