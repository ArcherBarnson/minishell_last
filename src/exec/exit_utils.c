/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:39:01 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/06 11:00:10 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_exit(int status, t_shell *shell, char **av, int fork)
{
	(void)av;
	if (fork == 1)
	{
		free(shell->cmd->cmd);
		free_all(shell);
		exit(status);
	}
	free_all(shell);
	exit(status);
}

long long	ft_atoll(const char	*str)
{
	int					i;
	long long			sign;
	long long			tot;

	i = 0;
	sign = 1;
	tot = 0;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		tot = tot * 10 + (str[i] - '0');
		i++;
	}
	return (tot * sign);
}
