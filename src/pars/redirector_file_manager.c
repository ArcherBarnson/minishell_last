/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector_file_manager.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 12:56:48 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_infile(t_pars *pars, char *file)
{
	if (!file)
		return (1);
	if (pars->fd_in)
		close (pars->fd_in);
	pars->fd_in = open(file, O_RDWR);
	if (pars->fd_in < 0)
	{
		ft_msgerr(ERR_FILEIN);
		return (-1);
	}
	return (0);
}

int	ft_open_outfile(t_pars *pars, char *file)
{
	if (!file)
		return (1);
	if (pars->fd_out != 1)
		close (pars->fd_out);
	pars->fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (pars->fd_out < 0)
	{
		ft_msgerr(ERR_FILEOUT);
		return (-1);
	}
	return (0);
}

int	ft_open_append_outfile(t_pars *pars, char *file)
{
	if (!file)
		return (1);
	if (pars->fd_out != 1)
		close (pars->fd_out);
	pars->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (pars->fd_out < 0)
	{
		ft_msgerr(ERR_FILEOUT);
		return (-1);
	}
	return (0);
}
