/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:38:41 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/01 11:02:03 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_unsetcmp(char *s1_lst, char*s2)
{
	int	i;

	i = 0;
	while (s1_lst[i] && s2[i])
	{
		if (s1_lst[i] == '=')
			break ;
		if (s1_lst[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i] == '\0' && (s1_lst[i] == '\0' || s1_lst[i] == '='))
		return (1);
	return (0);
}

void	remove_var_if_present(char *var, t_envp_cpy **envpc_lst)
{
	t_envp_cpy	*tmp;
	t_envp_cpy	*tmp_previous;

	if (!envpc_lst || !(*envpc_lst))
		return ;
	tmp = *envpc_lst;
	tmp_previous = NULL;
	while (tmp)
	{
		if (ft_unsetcmp(tmp->var, var))
		{
			if (tmp_previous)
				tmp_previous->next = tmp->next;
			else
				*envpc_lst = tmp->next;
			free(tmp->var);
			free(tmp);
			return ;
		}
		tmp_previous = tmp;
		tmp = tmp->next;
	}
}

int	is_unset_valid_string(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '=')
		return (0);
	if ((str[0] < 'A' || str[0] > 'Z')
		&& (str[0] < 'a' || str[i] > 'z') && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (!is_valid_identifier(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	unset(int ac, char **av, t_envp_cpy **envpc_lst)
{
	int						i;

	i = 1;
	while (i < ac)
	{
		if (is_unset_valid_string(av[i]))
			remove_var_if_present(av[i], envpc_lst);
		i++;
	}
	return (0);
}
