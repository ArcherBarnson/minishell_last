/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:53:58 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/29 20:31:11 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_error(char *str, int i, int error_type)
{
	if (error_type == 0)
	{
		write(2, "Needs a variable name before '=' operator\n", 43);
		return (0);
	}
	if (error_type == 1)
	{
		write(2, &str[i], 1);
		write(2, " : Invalid identifier before '='\n", 34);
		return (0);
	}
	return (0);
}

int	is_env_var(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str[i] == '=' && str[i + 1] != '\0')
		return (1);
	return (0);
}

int	is_valid_identifier(char c)
{
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')
		&& (c < '0' || c > '9') && c != '_')
		return (0);
	return (1);
}

int	is_valid_string(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (export_error(str, 0, 0));
	if ((str[0] < 'A' || str[0] > 'Z')
		&& (str[0] < 'a' || str[i] > 'z') && str[0] != '_')
		return (export_error(str, 0, 1));
	while (str[i] && str[i] != '=')
	{
		if (str[i + 1] == '=' && str[i] == '+')
			return (2);
		if (!is_valid_identifier(str[i]))
			return (export_error(str, i, 1));
		i++;
	}
	return (1);
}

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
