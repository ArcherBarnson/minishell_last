/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 05:00:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:29:58 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_hdoc_list(t_pars *pars)
{
	t_hdoc	*start;
	int		found;

	found = ft_strcmp(pars->current_filename, pars->hdoc_list->file_name);
	if (found == 1)
	start = pars->hdoc_list;
	pars->hdoc_list = pars->hdoc_list->next;
	while (!found && pars->hdoc_list != start)
	{
		found = ft_strcmp(pars->current_filename, pars->hdoc_list->file_name);
		pars->hdoc_list = pars->hdoc_list->next;
	}
	if (!found)
		return (ft_msgerr(ERR_NAMEHDOC));
	else
	{
		free(pars->hdoc_list->file_name);
		pars->hdoc_list->file_name = ft_strdup(pars->new_filename);
		pars->hdoc_list->fd = pars->new_fd;
		free(pars->new_filename);
	}
	return (0);
}

int	ft_update_command_fds(t_pars *pars)
{
	int	i;

	i = 0;
	while (i++ < pars->nb_of_commands)
	{
		if (pars->command->fd_in == pars->current_fd)
			pars->command->fd_in = pars->new_fd;
		if (pars->command->fd_out == pars->current_fd)
			pars->command->fd_out = pars->new_fd;
		pars->command = pars->command->next;
	}
	return (0);
}

int	ft_debug_hdoc_list(t_hdoc *hdoc)
{
	int	count;
	int	i;

	count = ft_count_list(hdoc);
	i = 0;
	if (count)
	{
		while (i < count)
		{
			hdoc = hdoc->next;
			i++;
		}
	}
	return (0);
}

int	ft_free_commandtokenlol(t_command *command)
{
	t_command	*temp;

	if (!command || !command->nb_of_tokens)
		return (1);
	while (1)
	{
		temp = command;
		command = ft_command_jumpcurrent(command->prev, command->next);
		ft_free_tokenlist(&(temp->token));
		if (command == temp)
		{
			command = NULL;
			break ;
		}
		temp = NULL;
	}
	command = NULL;
	return (0);
}
