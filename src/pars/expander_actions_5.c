/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:36:03 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 19:59:52 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_envstr(char *str, t_pars *pars)
{
	int		i;
	int		k;
	char	*comp_str;

	i = 0;
	while (pars->ms_env[i])
	{
		k = ft_strkchr(pars->ms_env[i], '=');
		if (k == -1)
			return (NULL);
		comp_str = ft_substr(pars->ms_env[i], 0, k);
		if (!ft_strncmp(str, comp_str, ft_strlen(str)))
		{
			free(comp_str);
			return (pars->ms_env[i] + k + 1);
		}
		free(comp_str);
		i++;
	}
	return (NULL);
}

int	ft_exp_end(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_err(t_pars *pars)
{
	return (1 + pars->new_exp_decision.exp_read_mode);
}
