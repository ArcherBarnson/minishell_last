/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:39:27 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/21 08:21:41 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

int	env(int ac, char **av, char **envp)
{
	int	i;

	i = 0;
	(void)av;
	if (ac != 1 || !envp)
		return (0);
	while (envp[i] != NULL)
	{
		printf("DEBUG");
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
