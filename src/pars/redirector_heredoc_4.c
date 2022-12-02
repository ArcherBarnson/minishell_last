/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 05:00:37 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 11:10:23 by mbourgeo         ###   ########.fr       */
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
		//printf("initial fd in and out are <%d> <%d> \n",
		//	pars->command->fd_in, pars->command->fd_out);
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
		//printf("\nHDOC_LIST CONTENT\n");
		while (i < count)
		{
			//printf("\033[33;2m<%d> %s\033[0m\n", hdoc->fd, hdoc->file_name);
			hdoc = hdoc->next;
			i++;
		}
	}
	return (0);
}
