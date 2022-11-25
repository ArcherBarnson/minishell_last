/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 18:23:52 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_redir_actions(t_pars *pars)
{
	pars->ft_redir[REDIR_NONE] = ft_redir_none;
	pars->ft_redir[REDIR_NEW] = ft_redir_new;
	pars->ft_redir[REDIR_CATCH] = ft_redir_catch;
	pars->ft_redir[REDIR_KEEP] = ft_redir_keep;
	pars->ft_redir[REDIR_DROP] = ft_redir_drop;
	pars->ft_redir[REDIR_TAKE] = ft_redir_take;
	pars->ft_redir[REDIR_SKIP] = ft_redir_skip;
	pars->ft_redir[REDIR_IN] = ft_redir_in;
	pars->ft_redir[REDIR_HDOC] = ft_redir_heredoc;
	pars->ft_redir[REDIR_OUT] = ft_redir_out;
	pars->ft_redir[REDIR_OUT_APPEND] = ft_redir_out_append;
	pars->ft_redir[REDIR_DEL_TWO] = ft_redir_del_two;
	pars->ft_redir[REDIR_END] = ft_redir_end;
	pars->ft_redir[REDIR_ERR] = ft_redir_err;
	return (0);
}

int	ft_redir_none(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_new(t_pars *pars)
{
	int	id;

	id = 0;
	if (pars->command)
	{
		pars->command->token = pars->command->token->next;
		id = pars->command->id;
	}
	pars->command = ft_command_addnext(pars->command,
			ft_new_command(pars->token));
	id++;
	pars->nb_of_commands++;
	pars->command->nb_of_tokens = 1;
	pars->command->id = id;
	return (0);
}

int	ft_redir_catch(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_keep(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_drop(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_take(t_pars *pars)
{
	if (!pars->command)
		ft_redir_new(pars);
	else
	{
		pars->command->token = ft_token_addnext(pars->command->token,
				ft_new_token(pars->token->id));
		pars->command->nb_of_tokens++;
	}
	pars->command->token->type = pars->token->type;
	return (0);
}

int	ft_redir_skip(t_pars *pars)
{
	pars->nb_of_tokens--;
	pars->token = pars->token->next;
	return (0);
}

int	ft_redir_record(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_in(t_pars *pars)
{
	int	ret;

	pars->current_filename = pars->command->token->next->id;
	if (ft_is_hdoc(pars->current_filename, pars))
		ft_change_hdoc_filename(pars);
	ret = 0;
	ret = ft_open_infile(pars, pars->command->token->next->id);
	if (!ret)
		pars->command->fd_in = pars->fd_in;
	else
		pars->command->fd_in = -1;
	return (ret);
}

int	ft_redir_heredoc(t_pars *pars)
{
	int		ret;
	t_hdoc	*hdoc_current;

	if (pars->prev_redir_decision.redir_read_mode == HDOC_REDIR_RD_MD)
	{
		printf("consecutive heredocs\n");
		unlink(pars->hdoc_list->file_name);
		hdoc_current = pars->hdoc_list->prev;
		pars->hdoc_list = ft_hdoc_list_freeone(pars->hdoc_list);
		if (pars->hdoc_list)
			pars->hdoc_list = hdoc_current;
		pars->hdoc_i--;
	}
	ret = 0;
	ret = ft_open_heredoc(pars, pars->command->token->next->id);
	if (!ret)
		pars->command->fd_in = pars->fd_in;
	else
		pars->command->fd_in = -1;
	return (ret);
}

int	ft_redir_out(t_pars *pars)
{
	int	ret;

	printf("in redir_out\n");
	pars->current_filename = pars->command->token->next->id;
	if (ft_is_hdoc(pars->current_filename, pars))
	{
		printf("name was found in heredoc list\n");
		printf("will now change name in hdoc\n");
		ft_change_hdoc_filename(pars);
	}
	ret = 0;
	ret = ft_open_outfile(pars, pars->command->token->next->id);
	if (!ret)
		pars->command->fd_out = pars->fd_out;
	else
		pars->command->fd_out = -1;
	return (ret);
}

int	ft_redir_out_append(t_pars *pars)
{
	int	ret;

	pars->current_filename = pars->command->token->next->id;
	if (ft_is_hdoc(pars->current_filename, pars))
		ft_change_hdoc_filename(pars);
	ret = 0;
	ret = ft_open_append_outfile(pars, pars->command->token->next->id);
	if (!ret)
		pars->command->fd_out = pars->fd_out;
	else
		pars->command->fd_out = -1;
	return (ret);
}

int	ft_redir_del_two(t_pars *pars)
{
	//printf("token : %s\n", pars->token->id);
	pars->token = ft_free_one_token(pars->token);
	pars->command->nb_of_tokens--;
	pars->token = ft_free_one_token(pars->token);
	pars->command->nb_of_tokens--;
	pars->token = pars->token->prev->prev;
	pars->command->token = pars->token;
	return (0);
}

int	ft_redir_end(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_redir_err(t_pars *pars)
{
        return(1 + pars->new_redir_decision.redir_read_mode);
}
