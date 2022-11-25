/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 19:14:04 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_exp_actions(t_pars *pars)
{
	pars->ft_exp[EXP_NONE] = ft_exp_none;
	pars->ft_exp[EXP_ANALYSIS] = ft_exp_analysis;
	pars->ft_exp[EXP_CATCH] = ft_exp_catch;
	pars->ft_exp[EXP_KEEP] = ft_exp_keep;
	pars->ft_exp[EXP_REC] = ft_exp_record;
	pars->ft_exp[EXP_DROP] = ft_exp_drop;
	pars->ft_exp[EXP_TAKE] = ft_exp_take;
	pars->ft_exp[EXP_SKIP] = ft_exp_skip;
	pars->ft_exp[EXP_DOL] = ft_exp_dol;
	pars->ft_exp[EXP_END] = ft_exp_end;
	pars->ft_exp[EXP_ERR] = ft_exp_err;
	return (0);
}

int	ft_exp_none(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_analysis(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_new(t_pars *pars)
{
	int	id;

	id = 0;
	if (pars->command)
	{
		pars->command->token = pars->command->token->next;
		id = pars->command->id;
	}
	pars->command = ft_command_addnext(pars->command, ft_new_command(pars->token));
	id++;
	pars->nb_of_commands++;
	pars->command->nb_of_tokens = 1;
	pars->command->id = id;
	return (0);
}

int	ft_exp_catch(t_pars *pars)
{
	ft_exp_record(pars);
	if (pars->temp)
	{
		free(pars->token->id);
		pars->token->id = NULL;
		pars->token->id = ft_strndup(pars->temp, 0);
		pars->token->type = pars->prev_exp_decision.token_type;
		free(pars->temp);
		pars->temp = NULL;
	}
	else
	{
		free(pars->token->id);
		pars->token->id = NULL;
		pars->token->id = ft_strndup("", 0);
		pars->token->type = pars->prev_exp_decision.token_type;
	}
	return (0);
}

int	ft_exp_keep(t_pars *pars)
{
//	(void)pars;
	printf("********temp : %s\n", pars->temp);
	return (0);
}

int	ft_exp_drop(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_take(t_pars *pars)
{
	if (!pars->nb_taken_char && !pars->before_dol_mode)
		pars->start_std = pars->offset_start;
	pars->nb_taken_char++;
	return (0);
}

int	ft_exp_skip(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_record(t_pars *pars)
{
	char	*temp1;
	char	*temp2;

	if (pars->nb_taken_char)
	{
		if (pars->temp)
		{
			temp1 = ft_strndup(pars->temp, 0);
			free(pars->temp);
		}
		else
			temp1 = ft_strndup("", 0);
		temp2 = ft_substr(pars->parser_text - pars->offset_start,
				pars->start_std, pars->nb_taken_char);
		pars->temp = ft_tempjoin(temp1, temp2);
		ft_init_expander(pars);
	}
	return (0);
}

/*char	*ft_init_exp_temp(t_pars *pars)
{
	pars->temp = malloc(sizeof(char));
	if (!pars->temp)
		return (ft_msgerr(ERR_MALLOC), NULL);
	ft_bzero(pars->temp, sizeof(char));
	return (pars->temp);
}*/

char	*ft_tempjoin(char *temp1, char *temp2)
{
	char	*temp;

	temp = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	temp1 = NULL;
	temp2 = NULL;
	return (temp);
}

char	*ft_getenv(char *temp)
{
	char	*temp2;

	if (!getenv(temp))
	{
		free(temp);
		temp2 = ft_strndup("", 0);
	}
	else
	{
		temp2 = ft_strndup(getenv(temp), 0);
		free(temp);
	}
	return (temp2);
}

int	ft_exp_record_dol(t_pars *pars)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	if (pars->nb_taken_char)
	{
		if (!pars->temp)
		{
			pars->temp = malloc(sizeof(char));
			ft_bzero(pars->temp, sizeof(char));
			temp1 = pars->temp;
		}
		else
		{
			temp1 = ft_strndup(pars->temp, 0);
			free(pars->temp);
		}
		temp = ft_substr(pars->parser_text - pars->offset_start,
				pars->start_dol, pars->nb_taken_char);
		temp2 = ft_getenv(temp);
		pars->temp = ft_tempjoin(temp1, temp2);
		ft_init_expander(pars);
	}
	return (0);
}

int	ft_exp_dol(t_pars *pars)
{
	if (!pars->start_dol)
	{
		printf("--------------------START_1\n");
		pars->start_dol = pars->offset_start + 1;
		pars->before_dol_mode = pars->prev_exp_decision.exp_read_mode;
	}
	else
	{
		printf("--------------------START_2\n");
		ft_exp_record_dol(pars);
		printf("temp : %s\n", pars->temp);
		if (pars->new_exp_decision.exp_read_mode == DOL_EXP_RD_MD)
			pars->start_dol = pars->offset_start + 1;
		else
		{
			if (pars->before_dol_mode == DBL_EXP_RD_MD)
			{
				if (pars->new_exp_decision.exp_read_mode == DBL_EXP_RD_MD)
					pars->new_exp_decision.exp_read_mode = STD_EXP_RD_MD;
				else
				{
					printf("--------------------HERE\n");
					pars->new_exp_decision.exp_read_mode = pars->before_dol_mode;
				}
				pars->before_dol_mode = CMB_ERR_EXP_RD_MD;
			}
		}
	}
	return (0);
}

int	ft_exp_end(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_err(t_pars *pars)
{
	return(1 + pars->new_exp_decision.exp_read_mode);
	//return (ft_msgerr(ft_getlabel_error_msgs((t_err_msgs)
	//			pars->new_exp_decision.token_type)), 0);
}
