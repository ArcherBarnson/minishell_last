/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:36:03 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:36:10 by mbourgeo         ###   ########.fr       */
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
		k = ft_find_eq(pars->ms_env[i]) - 1;
		if (k == 0)
			return (NULL);
		comp_str = ft_substr(pars->ms_env[i], 0, k + 1);
		if (!ft_strncmp(str, comp_str, ft_strlen(str)))
		{
			free(comp_str);
			return (pars->ms_env[i] + k + 2);
		}
		free(comp_str);
		i++;
	}
	return (NULL);
}

int	ft_find_eq(char *env_str)
{
	int	start;

	start = 0;
	start = ft_strkchr(env_str, '=');
	if (start == -1)
		return (ft_msgerr(ERR_EQNOTFOUND));
	return (start);
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
