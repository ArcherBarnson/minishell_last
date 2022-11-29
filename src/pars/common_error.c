/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/29 01:03:40 by mbourgeo         ###   ########.fr       */
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
		exit_code = 2;
	return (printf("\033[0;31m%s\n\033[0m", str), 1);
	//return (printf("%s\n", str), 1);
}
