/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:44:12 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/15 21:46:57 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_mem_alloc(int n)
{
	char	*str;
	char	*str_cpy;

	str = malloc((n) * sizeof(char));
	if (!str)
		return (NULL);
	str_cpy = str;
	while (n-- > 0)
		*str_cpy++ = '\0';
	return (str);
}

int	ft_strlen2(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		s++;
		count++;
	}
	return (count);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	char	*str_cpy;
	int		length;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	length = ft_strlen2(s1) + ft_strlen2(s2);
	str = ft_mem_alloc(length + 1);
	str_cpy = str;
	while (s1[i])
		*str_cpy++ = s1[i++];
	i = 0;
	while (s2[i])
		*str_cpy++ = s2[i++];
	*str_cpy = '\0';
	free(s1);
	free(s2);
	return (str);
}

char	*ft_substr2(char **s, int start, int length)
{
	char	*str;
	int		shift;
	int		len_s;

	if (*s == NULL)
		return (NULL);
	len_s = ft_strlen2(*s);
	if (start >= len_s)
		length = 0;
	else if (start + length >= len_s)
		length = len_s - start;
	if (length == 0)
	{
		free(*s);
		return (NULL);
	}
	str = ft_mem_alloc(length + 1);
	shift = -1;
	while (++shift < length)
		*(str + shift) = *((*s + shift) + start);
	*(str + shift) = '\0';
	if (start != 0)
		free(*s);
	return (str);
}

int	ft_index_nl(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	if (str[count] == '\0')
		return (-1);
	return (count);
}
