/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:15:16 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/18 11:51:29 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	pwd(int ac, char **av)
{
	char cwd[4096];

	(void)av;
	if (ac > 1)
	{
		write(2, "Too many arguments\n", 19);
		return (-1);
	}
	getcwd(cwd, 4096);
	write(1, &cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}
