/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:18:49 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:56:43 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_heredoc(t_pars *pars, char *delim)
{
	char	*file_name;

	pars->hdoc_i++;
	file_name = ft_generate_valid_hdoc_name(pars);
	pars->fd_in = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (pars->fd_in < 0)
		return (ft_msgerr(ERR_FILEHDOC));
	ft_inner_loop_heredoc(pars, delim);
	close(pars->fd_in);
	pars->fd_in = open(file_name, O_RDWR);
	pars->hdoc_list = ft_hdoc_addnext(pars->hdoc_list,
			ft_new_hdoc(file_name, pars->fd_in));
	free(file_name);
	return (0);
}

int	ft_inner_loop_heredoc(t_pars *pars, char *delim)
{
	char	*str_gnl;

	while (1)
	{
		write(1, ">", 1);
		str_gnl = get_next_line(0);
		if (str_gnl)
		{
			if (!ft_strncmp(str_gnl, delim, ft_strlen(delim))
				&& ft_strlen(delim) == ft_strlen(str_gnl) - 1)
				break ;
			else
			{
				write(pars->fd_in, str_gnl, ft_strlen(str_gnl));
				free(str_gnl);
			}
		}
	}
	free(str_gnl);
	return (0);
}

t_hdoc	*ft_new_hdoc(char *str, int fd)
{
	t_hdoc	*new;

	if (ft_mallocator(&new, sizeof(t_hdoc)))
		return (0);
	new->file_name = ft_strdup(str);
	new->fd = fd;
	new->prev = new;
	new->next = new;
	return (new);
}

t_hdoc	*ft_hdoc_addnext(t_hdoc *current, t_hdoc *next)
{
	if (!current)
		return (current = next, current);
	else if (!next)
		return (ft_msgerr(ERR_NULLHDOC), NULL);
	else
	{
		next->prev = current;
		next->next = current->next;
		current->next->prev = next;
		current->next = next;
	}
	return (next);
}

t_hdoc	*ft_hdoc_jumpcurrent(t_hdoc *prev, t_hdoc *next)
{
	if (next->next != next)
	{
		prev->next = next;
		next->prev = prev;
	}
	return (next);
}
