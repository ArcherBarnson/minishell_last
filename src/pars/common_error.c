/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 03:00:35 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_msgerr(char *str)
{
	if (ft_strcmp(str, ERR_CMB)
		|| ft_strcmp(str, ERR_SYN)
		|| ft_strcmp(str, ERR_CHR)
		|| ft_strcmp(str, ERR_SPL)
		|| ft_strcmp(str, ERR_DBL))
		g_exit_code = 2;
	return (printf("%s\n", str), 1);
}
