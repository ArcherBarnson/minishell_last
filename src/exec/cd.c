/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:12:14 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/09 12:12:17 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	cd(int ac, char **path)
{
	if (ac != 2)
	{
		write(1, "Wrong number of arguments\n", 27);
		return (-1);
	}
	chdir(path[1]);
	return (0);
}
