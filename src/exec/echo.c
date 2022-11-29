/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:42:06 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/29 20:17:23 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

void	write_arg(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	return ;
}

int	n_flag_present(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
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

int	echo(int ac, char **av, int fd)
{
	int	i;

	i = 1;
	if (!av[1])
	{
		write(fd, "\n", 1);
		return (0);
	}
	while (n_flag_present(av[i]) == 1)
		i++;
	while (av[i] && i < ac)
	{
		write_arg(av[i], fd);
		if (av[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
	if (n_flag_present(av[1]) != 1)
		write(fd, "\n", 1);
	return (0);
}
