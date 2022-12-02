/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:35:24 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/01 23:40:47 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = (long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = (long)-n;
		if (n == -2147483648)
		{
			write (fd, "2147483648", 10);
			return ;
		}
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	c = nb % 10 + '0';
	write(fd, &c, 1);
}

void	ft_shlvl(char *var, char *tmp2, int sh)
{
	tmp2 = ft_strdup(var + 6);
	sh = ft_atoll(tmp2) + 1;
	if (sh > 999)
	{
		write(2, "minishell: warning: shell level ", 32);
		ft_putnbr_fd(sh, 2);
		write(2, " too high, resetting to 1\n", 26);
		sh = 1;
	}
	else if (sh < 0)
		sh = 0;
	free(tmp2);
	tmp2 = ft_itoa(sh);
	free(var);
	var = ft_strjoin("SHLVL=", tmp2);
	free(tmp2);
}
