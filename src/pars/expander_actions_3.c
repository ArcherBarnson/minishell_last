/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:36:33 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/01 04:36:36 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exp_record(t_pars *pars)
{
	char	*temp1;
	char	*temp2;

	if (pars->nb_taken_char)
	{
		if (pars->temp)
		{
			temp1 = ft_strdup(pars->temp);
			free(pars->temp);
		}
		else
			temp1 = ft_strdup("");
		temp2 = ft_substr(pars->parser_text - pars->offset_start,
				pars->start_std, pars->nb_taken_char);
		pars->temp = ft_tempjoin(&temp1, &temp2);
		ft_init_expander(pars);
	}
	return (0);
}

char	*ft_tempjoin(char **temp1, char **temp2)
{
	char	*temp;

	temp = ft_strjoin(*temp1, *temp2);
	free(*temp1);
	free(*temp2);
	*temp1 = NULL;
	*temp2 = NULL;
	return (temp);
}

char	*ft_getenv(char *temp, t_pars *pars)
{
	char	*temp2;

	if (!ft_find_envstr(temp, pars))
	{
		free(temp);
		temp2 = ft_strdup("");
	}
	else
	{
		temp2 = ft_strdup(ft_find_envstr(temp, pars));
		free(temp);
	}
	return (temp2);
}
