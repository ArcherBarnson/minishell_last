/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:58:17 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/24 11:42:31 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	strcmp_diff(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

void	sort_env_args(char **envpc, char *tmp, int i, int j)
{
	while (envpc[j])
	{
		while (envpc[i])
		{
			if (strcmp_diff(envpc[j], envpc[i]) > 0)
			{
				tmp = envpc[i];
				envpc[i] = envpc[j];
				envpc[j] = tmp;
			}
			i++;
		}
		j++;
		i = j + 1;
	}
	return ;
}

void	export_no_args(t_envp_cpy *envpc_lst)
{
	char	**envpc;
	char	*tmp;
	int	i;
	int	j;

	i = 1;
	j = 0;
	envpc = lst_to_envp(envpc_lst);
	tmp = NULL;
	if (!envpc)
		return ;
	sort_env_args(envpc, tmp, i, j);
	env(1, NULL, envpc, 1);
	free(envpc);
	free(tmp);
	return ;
}