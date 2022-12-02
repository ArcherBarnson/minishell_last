/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:34:48 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 00:42:20 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strccmp(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] != c && s2[i] != c
		&& s1[i] == s2[i] && s1[i] != '+')
		i++;
	if (s1[i] == s2[i] || (s1[i] == '+' && s2[i] == '='))
		return (0);
	return (1);
}

char	*ft_strdup_offset(char *str, int offset)
{
	int		size;
	char	*returnstr;

	size = 0;
	if (!str)
		return (NULL);
	while (str[offset])
	{
		offset++;
		size++;
	}
	returnstr = malloc(sizeof(char) * (size + 1));
	if (!returnstr)
		return (NULL);
	offset -= size;
	size = 0;
	while (str[++offset])
	{
		returnstr[size] = str[offset];
		size++;
	}
	returnstr[size] = '\0';
	return (returnstr);
}

char	*get_home_path(char **envp)
{
	char	*home;
	int		i;

	i = 0;
	home = NULL;
	while (envp[i] && ft_strccmp("HOME=", envp[i], '=') != 0)
		i++;
	if (envp[i] != NULL)
		home = ft_strdup_offset(envp[i], 4);
	return (home);
}
