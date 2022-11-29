/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strkchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 21:33:47 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/29 04:20:42 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strkchr(const char *s, int c)
{
	int	k;

	k = 0;
	while (*s && (unsigned char)c != *s)
	{
		k++;
		s++;
	}
	if (!*s && (unsigned char)c)
		return (-1);
	return (k);
}
