/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 04:36:38 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/02 20:01:21 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exp_record_dol(t_pars *pars)
{
	char	*temp1;

	if (!pars->temp)
	{
		pars->temp = malloc(sizeof(char));
		ft_bzero(pars->temp, sizeof(char));
		temp1 = pars->temp;
	}
	else
	{
		temp1 = ft_strdup(pars->temp);
		free(pars->temp);
		pars->temp = NULL;
	}
	if (pars->nb_taken_char)
		ft_exp_record_dol_part2(pars, temp1);
	else
		ft_exp_record_dol_part3(pars, temp1);
	ft_init_expander(pars);
	return (0);
}

int	ft_exp_record_dol_part2(t_pars *pars, char *temp1)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(pars->parser_text - pars->offset_start,
			pars->start_dol, pars->nb_taken_char);
	if (ft_strcmp(temp, "?"))
	{
		temp2 = ft_itoa(g_exit_code);
		pars->temp = ft_tempjoin(&temp1, &temp2);
		pars->new_exp_decision.exp_read_mode = NEW_EXP_RD_MD;
	}
	else
	{
		temp2 = ft_getenv(temp, pars);
		temp = NULL;
		pars->temp = ft_tempjoin(&temp1, &temp2);
	}
	free(temp);
	return (0);
}

int	ft_exp_record_dol_part3(t_pars *pars, char *temp1)
{
	char	*temp2;

	if (pars->new_exp_decision.exp_read_mode == DOL_EXP_RD_MD)
	{
		temp2 = ft_strdup("$$");
		pars->temp = ft_tempjoin(&temp1, &temp2);
		pars->new_exp_decision.exp_read_mode = NEW_EXP_RD_MD;
	}
	else
	{
		temp2 = ft_strdup("$");
		pars->temp = ft_tempjoin(&temp1, &temp2);
	}
	return (0);
}

int	ft_exp_dol(t_pars *pars)
{
	if (!pars->start_dol)
	{
		if (pars->nb_taken_char)
			ft_exp_record(pars);
		pars->start_dol = pars->offset_start + 1;
		pars->before_dol_mode = pars->prev_exp_decision.exp_read_mode;
	}
	else
	{
		ft_exp_record_dol(pars);
		if (pars->new_exp_decision.exp_read_mode == DOL_EXP_RD_MD)
			pars->start_dol = pars->offset_start + 1;
		else if (pars->before_dol_mode == DBL_EXP_RD_MD)
		{
			if (pars->new_exp_decision.exp_read_mode == DBL_EXP_RD_MD)
				pars->new_exp_decision.exp_read_mode = STD_EXP_RD_MD;
			else
				pars->new_exp_decision.exp_read_mode
					= pars->before_dol_mode;
			pars->before_dol_mode = CMB_ERR_EXP_RD_MD;
		}
	}
	return (0);
}
