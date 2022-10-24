/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:18:49 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 18:23:27 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_heredoc(t_pars *pars, char *delim)
{
	char	*file_name;

	pars->hdoc_i++;
	file_name = ft_generate_valid_hdoc_name(pars);
	pars->fd_in = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (pars->fd_in < 0)
		return (ft_msgerr(ERR_FILEHDOC));
	ft_inner_loop_heredoc(pars, delim);
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
	new->file_name = ft_strndup(str, 0);
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

t_hdoc	*ft_hdoc_list_freeone(t_hdoc *hdoc)
{
	int		ret;
	t_hdoc	*next;

	ret = 0;
	next = hdoc->next;
	if (hdoc->next == next)
		ret = 1;
	ft_hdoc_jumpcurrent(hdoc->prev, hdoc->next);
	free(hdoc->file_name);
	hdoc->file_name = NULL;
	free(hdoc);
	hdoc = NULL;
	if (ret == 1)
		return (NULL);
	else
		return (next);
}

int	ft_free_hdoclist(t_hdoc *hdoc)
{
	t_hdoc	*temp;

	if (!hdoc)
		return (1);
	while (1)
	{
		temp = hdoc;
		hdoc = ft_hdoc_jumpcurrent(hdoc->prev, hdoc->next);
		free(temp->file_name);
		free(temp);
		if (hdoc == temp)
			break ;
		temp = NULL;
	}
	hdoc = NULL;
	return (0);
}

int	ft_free_hdoctab(t_hdoc_tab *hdoc_tab)
{
	int	i;

	i = 0;
	if (hdoc_tab)
	{
		while (hdoc_tab[i].file_name)
		{
			free(hdoc_tab[i].file_name);
			hdoc_tab[i].file_name = NULL;
			i++;
		}
		free(hdoc_tab);
	}
	return (0);
}

int	ft_count_list(t_hdoc *hdoc)
{
	int		count;
	t_hdoc	*temp;

	count = 0;
	if (!hdoc)
		return (0);
	else
		count++;
	temp = hdoc;
	hdoc = hdoc->next;
	while (hdoc != temp)
	{
		count++;
		hdoc = hdoc->next;
	}
	return (count);
}

t_hdoc_tab	*ft_hdoc_list_to_tab(t_hdoc *hdoc, int count)
{
	int			i;
	t_hdoc_tab	*tab;

	i = 0;
	if (!count)
		return (NULL);
	tab = malloc((count + 1) * sizeof(t_hdoc_tab));
	if (!tab)
		return (ft_msgerr(ERR_MALLOC), NULL);
	while (i < count)
	{
		tab[i].file_name = ft_strdup(hdoc->file_name);
		tab[i].fd = hdoc->fd;
		hdoc = hdoc->next;
		i++;
	}
	tab[i].file_name = NULL;
	tab[i].fd = 0;
	return (tab);
}

int	ft_unlink_allhdoc(t_hdoc_tab *hdoc_tab)
{
	int	i;

	i = 0;
	if (hdoc_tab)
	{
		while (hdoc_tab[i].file_name)
		{
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
		printf("current hdoc_i : %d\n", pars->hdoc_i);
		printf("tentative name : %s\n", file_name);
		if (access(file_name, F_OK) && !ft_is_hdoc(file_name, pars))
			break ;
		free(file_name);
		pars->hdoc_i++;
	}
	printf("valid name : %s\n", file_name);
	return (file_name);
}

int	ft_change_hdoc_filename(t_pars *pars)
{
	pars->hdoc_i++;
	printf("***changing name and copying file from %s\n",
		pars->current_filename);
	pars->new_filename = ft_generate_valid_hdoc_name(pars);
	printf("...to chosen new name : %s\n", pars->new_filename);
	ft_copy_hdoc_new_name(pars);
	ft_update_hdoc_list(pars);
	ft_update_command_fds(pars);
	return (0);
}

int	ft_copy_hdoc_new_name(t_pars *pars)
{
	char	*str_gnl;

	printf("closing current_fd = %d\n", pars->current_fd);
	close(pars->current_fd);
	pars->current_fd = open(pars->current_filename, O_RDONLY, 0664);
	printf("opened current_hdocfile named <%s> with fd : %d\n",
		pars->current_filename, pars->current_fd);
	pars->new_fd = open(pars->new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	printf("opened new_hdocfile named <%s> with fd : %d\n",
		pars->new_filename, pars->new_fd);
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

//int	ft_update_hdoc_list(t_pars *pars)
//{
//	t_hdoc	*start;
//	int		found;
//
//	printf("\nin update_hdoc_list\n");
//	printf("start searching <%s> at <%s>\n",
//		pars->current_filename, pars->hdoc_list->file_name);
//	found = ft_strcmp(pars->current_filename, pars->hdoc_list->file_name);
//	if (found == 1)
//	start = pars->hdoc_list;
//	pars->hdoc_list = pars->hdoc_list->next;
//	while (!found && pars->hdoc_list != start)
//	{
//		found = ft_strcmp(pars->current_filename, pars->hdoc_list->file_name);
//		pars->hdoc_list = pars->hdoc_list->next;
//	}
//	if (!found)
//		return (ft_msgerr(ERR_NAMEHDOC));
//	else
//	{
//		printf("found, with fd <%d>\n", pars->hdoc_list->fd);
//		printf("name changed from <%s> to <%s>\n",
//			pars->hdoc_list->file_name, pars->new_filename);
//		printf("fd changed from <%d> to <%d>\n",
//			pars->hdoc_list->fd, pars->new_fd);
//		free(pars->hdoc_list->file_name);
//		pars->hdoc_list->file_name = ft_strdup(pars->new_filename);
//		pars->hdoc_list->fd = pars->new_fd;
//		free(pars->new_filename);
//	}
//	return (0);
//}

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
		printf("initial fd in and out are <%d> <%d> \n",
			pars->command->fd_in, pars->command->fd_out);
		if (pars->command->fd_in == pars->current_fd)
			pars->command->fd_in = pars->new_fd;
		if (pars->command->fd_out == pars->current_fd)
			pars->command->fd_out = pars->new_fd;
		pars->command = pars->command->next;
	}
	return (0);
}

int	ft_print_debug_hdoc_list(t_hdoc *hdoc)
{
	int	count;
	int	i;

	count = ft_count_list(hdoc);
	i = 0;
	if (count)
	{
		printf("\nHDOC_LIST CONTENT\n");
		while (i < count)
		{
			printf("\033[33;2m<%d> %s\033[0m\n", hdoc->fd, hdoc->file_name);
			hdoc = hdoc->next;
			i++;
		}
	}
	return (0);
}
