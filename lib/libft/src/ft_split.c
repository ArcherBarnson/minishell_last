/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:57:59 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/08 22:01:52 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	wc;
	int	i;

	wc = 0;
	i = 1;
	if (s == NULL || s[0] == '\0')
		return (0);
	if (s[0] != c)
		wc++;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			wc++;
		i++;
	}
	return (wc);
}

static void	free_if_error(char **strs, int strs_pos)
{
	while (strs_pos >= 0)
	{
		free(strs[strs_pos]);
		strs_pos--;
	}
	free(strs);
}

static void	malloc_and_cpy(char const *s, char c, char **strs, int strs_pos)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	strs[strs_pos] = malloc(sizeof(char) * (len + 1));
	if (!(strs[strs_pos]))
	{
		free_if_error(strs, strs_pos);
		return ;
	}
	while (i < len)
	{
		strs[strs_pos][i] = s[i];
		i++;
	}
	strs[strs_pos][i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] == c)
		i++;
	strs = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!(strs))
		return (NULL);
	while (j < word_count(s, c))
	{
		malloc_and_cpy(&s[i], c, strs, j);
		if (strs[j] == NULL)
			return (NULL);
		i += ft_strlen(strs[j]);
		while (s[i] == c)
			i++;
		j++;
	}
	strs[j] = 0;
	return (strs);
}
