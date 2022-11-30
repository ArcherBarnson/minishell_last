/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/30 16:19:03 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	exit_code;

int	ft_init_exp_actions(t_pars *pars)
{
	pars->ft_exp[EXP_NONE] = ft_exp_none;
	pars->ft_exp[EXP_NEW] = ft_exp_new;
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

//int	ft_initial_expansion()
//{
//}

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
	pars->command = ft_command_addnext(pars->command,
			ft_new_command(pars->token));
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
		pars->token->id = ft_strdup(pars->temp);
		pars->token->type = pars->prev_exp_decision.token_type;
		free(pars->temp);
		pars->temp = NULL;
	}
	else
	{
		free(pars->token->id);
		pars->token->id = NULL;
		pars->token->id = ft_strdup("");
		pars->token->type = pars->prev_exp_decision.token_type;
	}
	return (0);
}

int	ft_exp_keep(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_drop(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_take(t_pars *pars)
{
	if (!pars->nb_taken_char)
		pars->start_std = pars->offset_start;
	pars->nb_taken_char++;
	if (pars->nb_taken_char == 1 && !ft_strncmp(pars->parser_text, "?", 1))
		ft_exp_dol(pars);
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

int	ft_exp_record_dol(t_pars *pars)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	if (!pars->temp)
	{
		pars->temp = malloc(sizeof(char));
		ft_bzero(pars->temp, sizeof(char));
		temp1 = pars->temp;
	}
	else
		temp1 = ft_strdup(pars->temp);
	if (pars->nb_taken_char)
	{
		temp = ft_substr(pars->parser_text - pars->offset_start,
				pars->start_dol, pars->nb_taken_char);
		if (ft_strcmp(temp, "?"))
		{
			temp2 = ft_itoa(exit_code);
			temp = NULL;
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
	}
	else if (pars->new_exp_decision.exp_read_mode == DOL_EXP_RD_MD)
	{
		temp2 = ft_strdup("");
		pars->temp = ft_tempjoin(&temp1, &temp2);
		pars->new_exp_decision.exp_read_mode = NEW_EXP_RD_MD;
	}
	else
	{
		temp2 = ft_strdup("$");
		pars->temp = ft_tempjoin(&temp1, &temp2);
	}
	ft_init_expander(pars);
	free(temp1);
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
		else
		{
			if (pars->before_dol_mode == DBL_EXP_RD_MD)
			{
				if (pars->new_exp_decision.exp_read_mode == DBL_EXP_RD_MD)
					pars->new_exp_decision.exp_read_mode = STD_EXP_RD_MD;
				else
					pars->new_exp_decision.exp_read_mode
						= pars->before_dol_mode;
				pars->before_dol_mode = CMB_ERR_EXP_RD_MD;
			}
		}
	}
	return (0);
}

/*char	*ft_exp_excd(t_pars *pars)
{
	char	*exit_char_code;
	
	exit_char_code = ft_itoa(exit_code);
	pars->temp = ft_strdup(exit_char_code);
	free(exit_char_code);
	return (0);
}*/

char	*ft_find_envstr(char *str, t_pars *pars)
{
	int		i;
	int		k;
	char	*comp_str;

	i = 0;
	while (pars->ms_env[i])
	{
		k = ft_find_eq(pars->ms_env[i]) - 1;
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
