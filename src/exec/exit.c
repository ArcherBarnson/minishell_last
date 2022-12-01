/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:46:59 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/29 20:32:14 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	invalid_exit_arg(char *arg)
{
	(void)arg;
	write(2, "exit : numeric argument required\n", 34);
	return (0);
}

int	is_exit_arg_valid(char *arg)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(arg);
	if (arg[i] != '-' && (arg[i] < '0' || arg[i] > '9'))
		return (invalid_exit_arg(arg));
	if ((arg[i] == '-' && size > 20) || (arg[i] != '-' && size > 19))
		return (invalid_exit_arg(arg));
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (invalid_exit_arg(arg));
	}
	if ((ft_atoll(arg) > 0 && arg[0] == '-')
		|| (ft_atoll(arg) < 0 && arg[0] != '-'))
		return (invalid_exit_arg(arg));
	return (1);
}

int	get_formated_status(char *arg)
{
	long long	formated_status;

	if (is_exit_arg_valid(arg) == 0)
		return (2);
	formated_status = ft_atoll(arg);
	if (formated_status < 0)
		formated_status = 256 - ((-formated_status) % 256);
	else
		formated_status %= 256;
	return ((int)formated_status);
}

int	ft_exit(int ac, char **av, t_shell *shell, int fork)
{
	int	status;

	status = 2;
	write(1, "exit\n", 5);
	if (ac == 1 || av == NULL)
		clean_exit(g_exit_code, shell, av, fork);
	if (!is_exit_arg_valid(av[1]))
		clean_exit(status, shell, av, fork);
	if (ac > 2)
	{
		write(2, "Too many arguments\n", 20);
		return (1);
	}
	status = get_formated_status(av[1]);
	clean_exit(status, shell, av, fork);
	return (0);
}
