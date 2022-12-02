/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:57:10 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:30:28 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unlink_allhdoc(t_hdoc_tab *hdoc_tab)
{
	int	i;

	i = 0;
	if (hdoc_tab)
	{
		while (hdoc_tab[i].file_name)
		{
			close(hdoc_tab[i].fd);
			unlink(hdoc_tab[i].file_name);
			i++;
		}
	}
	return (0);
}

int	ft_is_hdoc(char *file_name, t_pars *pars)
{
	t_hdoc	*start;
	int		ret;

	ret = 0;
	if (!pars->hdoc_list)
		return (0);
	start = pars->hdoc_list;
	if (ft_strcmp(file_name, pars->hdoc_list->file_name))
	{
		pars->current_fd = pars->hdoc_list->fd;
		return (1);
	}
	pars->hdoc_list = pars->hdoc_list->next;
	while (pars->hdoc_list != start)
	{
		if (ft_strcmp(file_name, pars->hdoc_list->file_name))
		{
			pars->current_fd = pars->hdoc_list->fd;
			ret = 1;
		}
		pars->hdoc_list = pars->hdoc_list->next;
	}
	return (ret);
}

char	*ft_generate_valid_hdoc_name(t_pars *pars)
{
	char	*file_name;
	char	*temp1;
	char	*temp2;

	while (1)
	{
		temp1 = ft_itoa(pars->hdoc_i);
		temp2 = ft_strjoin(".heredoc_", temp1);
		free(temp1);
		temp1 = NULL;
		file_name = ft_strjoin(temp2, "_tmp");
		free(temp2);
		temp2 = NULL;
		if (access(file_name, F_OK) && !ft_is_hdoc(file_name, pars))
			break ;
		free(file_name);
		pars->hdoc_i++;
	}
	return (file_name);
}

int	ft_change_hdoc_filename(t_pars *pars)
{
	pars->hdoc_i++;
	pars->new_filename = ft_generate_valid_hdoc_name(pars);
	ft_copy_hdoc_new_name(pars);
	ft_update_hdoc_list(pars);
	ft_update_command_fds(pars);
	return (0);
}

int	ft_copy_hdoc_new_name(t_pars *pars)
{
	char	*str_gnl;

	close(pars->current_fd);
	pars->current_fd = open(pars->current_filename, O_RDWR, 0664);
	pars->new_fd = open(pars->new_filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (pars->new_fd < 0)
		return (ft_msgerr(ERR_FILECPY));
	str_gnl = get_next_line(pars->current_fd);
	while (str_gnl)
	{
		write(pars->new_fd, str_gnl, ft_strlen(str_gnl));
		free(str_gnl);
		str_gnl = get_next_line(pars->current_fd);
	}
	if (str_gnl)
		free(str_gnl);
	close (pars->current_fd);
	unlink (pars->current_filename);
	return (0);
}
