/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/29 04:32:39 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		sign;
	int		nb_carac;
	char	*str;

	nb_carac = ft_getsize(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc((nb_carac + 1) * sizeof(char));
	if (!str)
		return (NULL);
	sign = (n < 0);
	n = n - 2 * n * (n < 0);
	if (sign == 1)
		str[0] = '-';
	str[nb_carac] = '\0';
	while (nb_carac - sign)
	{
		str[nb_carac - 1] = n % 10 + '0';
		n = n / 10;
		nb_carac--;
	}
	return (str);
}
