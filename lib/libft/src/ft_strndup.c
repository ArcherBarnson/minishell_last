/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/28 12:07:57 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strndup(const char *s, size_t n)
{
        char    *cpy;
        int             i;

        if (!n)
                n = ft_strlen(s);
        cpy = malloc((n + 1) * sizeof(char));
        if (!cpy)
                return (NULL);
        i = 0;
        while (n--)
        {
                *(cpy + i) = *(s + i);
                i++;
        }
        *(cpy + i) = '\0';
        return (cpy);
}
