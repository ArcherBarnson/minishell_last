/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:15:16 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/29 20:16:04 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	pwd(int ac, char **av, int fd)
{
	char	cwd[4096];

	(void)av;
	(void)ac;
	getcwd(cwd, 4096);
	write(fd, &cwd, ft_strlen(cwd));
	write(fd, "\n", 1);
	return (0);
}
