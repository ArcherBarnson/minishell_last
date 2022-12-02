/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:15:16 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 16:08:10 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	pwd(int ac, char **av, int fd)
{
	char	*cwd;

	(void)av;
	(void)ac;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	write(fd, cwd, ft_strlen(cwd));
	write(fd, "\n", 1);
	free(cwd);
	return (0);
}
