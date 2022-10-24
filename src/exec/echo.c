/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:42:06 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/18 14:17:23 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

void	write_arg(char *str)
{
	write(1, str, ft_strlen(str));
	return ;
}

int	n_flag_present(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[++i])
		{
			if (str[i] != 'n' && str[i] != '\0')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	echo(int ac, char **av)
{
	int	i;

	i = 1;
	if (!av[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (n_flag_present(av[1]) == 1)
		i++;
	while (av[i] && i < ac)
	{
		if (!n_flag_present(av[1]) || !n_flag_present(av[i]))
		{
			write_arg(av[i]);
			if (av[i + 1] != NULL)
				write(1, " ", 1);
		}
		i++;
	}
	if (n_flag_present(av[1]) != 1)
		write(1, "\n", 1);
	return (0);
}
