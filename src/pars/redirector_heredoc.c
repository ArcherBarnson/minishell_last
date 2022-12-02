/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:18:49 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 04:28:26 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_heredoc(t_pars *pars, char *delim)
{
	char	*file_name;
	int		pid;
	int		status;

	pars->hdoc_i++;
	file_name = ft_generate_valid_hdoc_name(pars);
	pars->fd_in = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (pars->fd_in < 0)
		return (ft_msgerr(ERR_FILEHDOC));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		free(file_name);
		signal(SIGINT, sigint_heredoc);
		ft_inner_loop_heredoc(pars, delim);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 130)
	{
		write(1, "\n", 1);
		g_exit_code = 130;
		close(pars->fd_in);
		unlink(file_name);
		free(file_name);
		ft_lstclear(&free_heredoc(NULL, 1)->cmd, del);
		pars->ret_45 = 1;
		return (45);
	}
	close(pars->fd_in);
	pars->fd_in = open(file_name, O_RDWR);
	pars->hdoc_list = ft_hdoc_addnext(pars->hdoc_list,
			ft_new_hdoc(file_name, pars->fd_in));
	free(file_name);
	signal(SIGINT, sigint_handler);
	return (0);
}

int	ft_inner_loop_heredoc(t_pars *pars, char *delim)
{
	while (1)
	{
		pars->str_gnl = readline(">");
		if (pars->str_gnl)
		{
			if (!ft_strncmp(pars->str_gnl, delim, ft_strlen(delim))
				&& ft_strlen(delim) == ft_strlen(pars->str_gnl))
			{
				if (ft_transformer(pars))// || ft_debug_content(lex, pars, "trans"))
					return (ft_error_return(free_heredoc(NULL, 1)->lex, pars,(free_heredoc(NULL, 1))));
				ft_free_commandlist(pars->command);
				ft_tklist_freeall(free_heredoc(NULL, 1)->lex);
				ft_lstclear(&pars->cmd, del);
				free_all(free_heredoc(NULL, 1));
				free(pars->str_gnl);
				exit(0);
			}
			else
			{
				write(pars->fd_in, pars->str_gnl, ft_strlen(pars->str_gnl));
				write(pars->fd_in, "\n", 1);
				free(pars->str_gnl);
			}
		}
		else
		{
			if (ft_transformer(pars))// || ft_debug_content(lex, pars, "trans"))
				return (ft_error_return(free_heredoc(NULL, 1)->lex, pars,(free_heredoc(NULL, 1))));
			ft_free_commandlist(pars->command);
			ft_lstclear(&pars->cmd, del);
			ft_tklist_freeall(free_heredoc(NULL, 1)->lex);
			free_all(free_heredoc(NULL, 1));
			exit(0);
		}
	}
	free(pars->str_gnl);
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
