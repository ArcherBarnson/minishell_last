/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:12:14 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/22 11:21:25 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

char	*ft_strdup_offset(char *str, int offset)
{
	int	size;
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
	printf("%s\n", returnstr);
	return (returnstr);
}

char	*get_home_path(char **envp)
{
	char	*home;
	int	i;

	i = 0;
	home = NULL;
	while (envp[i] && ft_strccmp("HOME=", envp[i], '=') != 0)
		i++;
	if (envp[i] != NULL)
		home = ft_strdup_offset(envp[i], 4);
	return (home);
}

int	cd(int ac, char **path, char **envp)
{
	char	*home;

	home = get_home_path(envp);
	if (ac == 1)
	{
		if (home == NULL)
		{
			write(2, "cd : HOME not set\n", 19);
			return (1);
		}
		chdir(home);
		free(home);
		return (0);
	}
	if (ac > 2)
	{
		free(home);
		write(1, "Wrong number of arguments\n", 27);
		return (1);
	}
	free(home);
	chdir(path[1]);
	return (0);
}
