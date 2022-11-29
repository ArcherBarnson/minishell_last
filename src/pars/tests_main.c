/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/29 07:46:04 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code;

int	main(void)
{
	if (ft_tests())
		return (1);
	return (0);
}

int	ft_tests(void)
{
	int			fd;
	char		*user_input;
	//t_hdoc_tab	*hdoc_tab;
	t_shell		shell;

 	ft_bzero(&shell, sizeof(t_shell));
	fd = open("parser.test", O_RDONLY, 644);
	if (fd < 0)
		return (ft_msgerr(ERR_TESTFILE), 1);
	user_input = get_next_line(fd);
	while (user_input)
	{
		shell.retprompt = user_input;
		//ft_read_prompt(user_input, &hdoc_tab);
		ft_read_prompt(&shell);
		free(user_input);
		user_input = get_next_line(fd);
	}
	if (user_input)
	{
		free(user_input);
		user_input = NULL;
	}
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/29 07:40:02 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	exit_code;

int	ft_init_exp_actions(t_pars *pars)
{
	pars->ft_exp[EXP_NONE] = ft_exp_none;
	//pars->ft_exp[EXP_NEW] = ft_exp_new;
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

int	ft_exp_new(t_pars *pars, char *str)
{
	//ft_lex_record(lex);
	//lex->nb_taken_char = 0;
	if (str)
	{
		pars->token = ft_token_addnext(pars->token, ft_new_token(str));
		pars->command->nb_of_tokens++;
		pars->token->type = pars->prev_exp_decision.token_type;
		free(str);
		str = NULL;
	}
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
	(void)pars;
	//printf("********KEEP temp : %s\n", pars->temp);
	return (0);
}

int	ft_exp_drop(t_pars *pars)
{
	(void)pars;
	return (0);
}

int	ft_exp_take(t_pars *pars)
{
	//if (!pars->nb_taken_char && !pars->before_dol_mode)
	//printf("TAAAAAAAAAAAAAAAAAAAAAAAAAKING\n");
	if (!pars->nb_taken_char)
		pars->start_std = pars->offset_start;
	pars->nb_taken_char++;
	//printf("text = %s\n", pars->parser_text);
	//printf("nb_char = %d\n", pars->nb_taken_char);
	//printf("test = %d\n", ft_strncmp(pars->parser_text, "?", 1));
	//printf("char : %c\n", pars->parser_text[0]);
        //printf("type : %s\n", ft_getlabel_char_types(ft_char_type(pars->parser_text[0])));
        //printf("type : %s\n", ft_getlabel_exp_read_modes(pars->new_exp_decision.exp_read_mode));
	if (pars->nb_taken_char == 1 && !ft_strncmp(pars->parser_text, "?", 1))
	{
		//printf("entering\n");
		ft_exp_dol(pars);
	}
	//printf("start_std = %d\n", pars->start_std);
	//printf("offset_char = %d\n", pars->offset_start);
	//printf("nb_taken_char = %d\n", pars->nb_taken_char);
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

char	*ft_getenv(char *temp, t_pars *pars)
{
	char	*temp2;

	//if (!getenv(temp))
	if (!ft_find_envstr(temp, pars))
	{
		free(temp);
		temp2 = ft_strndup("", 0);
	}
	else
	{
		temp2 = ft_strndup(ft_find_envstr(temp, pars), 0);
		free(temp);
	}
	return (temp2);
}

int	ft_exp_record_dol(t_pars *pars)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	//printf("''''''''''''' RECORD_DOL\n");
	//printf("start_std = %d\n", pars->start_std);
	//printf("offset_char = %d\n", pars->offset_start);
	//printf("nb_taken_char = %d\n", pars->nb_taken_char);
		if (!pars->temp)
		{
			pars->temp = malloc(sizeof(char));
			ft_bzero(pars->temp, sizeof(char));
			temp1 = pars->temp;
		}
		else
		{
			temp1 = ft_strndup(pars->temp, 0);
			//printf("Here\n");
			//printf("temp1 = %s\n", temp1);
			//free(pars->temp);
		}
	if (pars->nb_taken_char)
	{
		temp = ft_substr(pars->parser_text - pars->offset_start,
				pars->start_dol, pars->nb_taken_char);
		if (ft_strcmp(temp, "?"))
		{
			//printf("Here\n");
			ft_exp_excd(pars);
			pars->new_exp_decision.exp_read_mode = NEW_EXP_RD_MD;
		}
		else
		{
			temp2 = ft_getenv(temp, pars);
			//printf("start_dol = %d\n", pars->start_dol);
			//printf("nb_taken_char = %d\n", pars->nb_taken_char);
			//printf("text = %s\n", pars->parser_text - pars->offset_start);
			//printf("temp = %s\n", temp);
			printf("******************temp2 = %s\n", temp2);
			printf("******************mode  = %s\n", ft_getlabel_exp_read_modes(pars->before_dol_mode));
			if (pars->before_dol_mode != DBL_EXP_RD_MD)
				ft_simple_split(pars, temp2);
			pars->temp = ft_tempjoin(temp1, temp2);
		}
	}
	else if (pars->new_exp_decision.exp_read_mode == DOL_EXP_RD_MD)
	{
		temp2 = ft_strdup("");
		pars->temp = ft_tempjoin(temp1, temp2);
		pars->new_exp_decision.exp_read_mode = NEW_EXP_RD_MD;
	}
	else
	{
		temp2 = ft_strdup("$");
		pars->temp = ft_tempjoin(temp1, temp2);
	}
	ft_init_expander(pars);
	return (0);
}

char	*ft_simple_split(t_pars *pars, char *str)
{
	char	*first_str;
	int		i;
	int		start;
	int		stop;

	i = 0;
	start = 0;
	stop = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ' && ++start)
			i++;
		stop = start;
		while (str[i] && str[i] != ' ' && ++stop)
			i++;
		if (stop > start)
		{
			printf("++++++++++++1st word is between : %d and : %d\n", start, stop - 1);
			printf("mn_tokens : %d\n", pars->command->nb_of_tokens);
			ft_exp_new(pars, ft_substr(str, start, stop - start));
			printf("mn_tokens : %d\n", pars->command->nb_of_tokens);
		}
		start = stop;
	}
	first_str = ft_strdup(str);
	return (first_str);
}

int	ft_exp_dol(t_pars *pars)
{
	//printf("enter exp_dol\n");
	//printf("char : %c\n", pars->parser_text[0]);
        //printf("type : %s\n", ft_getlabel_char_types(ft_char_type(pars->parser_text[0])));
        //printf("type : %s\n", ft_getlabel_exp_read_modes(pars->new_exp_decision.exp_read_mode));
	if (!pars->start_dol)
	{
		if (pars->nb_taken_char)
			ft_exp_record(pars);
		//printf("--------------------START_1\n");
		pars->start_dol = pars->offset_start + 1;
		pars->before_dol_mode = pars->prev_exp_decision.exp_read_mode;
	}
	else
	{
		//printf("--------------------START_2\n");
		ft_exp_record_dol(pars);
		//printf("temp : %s\n", pars->temp);
		if (pars->new_exp_decision.exp_read_mode == DOL_EXP_RD_MD)
			pars->start_dol = pars->offset_start + 1;
		else
		{
			//printf("--------------------START_1\n");
			//printf("before dol_mode : %d \n", pars->before_dol_mode);
			if (pars->before_dol_mode == DBL_EXP_RD_MD)
			{
				if (pars->new_exp_decision.exp_read_mode == DBL_EXP_RD_MD)
					pars->new_exp_decision.exp_read_mode = STD_EXP_RD_MD;
				else
					pars->new_exp_decision.exp_read_mode = pars->before_dol_mode;
				pars->before_dol_mode = CMB_ERR_EXP_RD_MD;
			}
			//else
			//{
			//	pars->new_exp_decision.exp_read_mode = CMB_ERR_EXP_RD_MD;
			//	pars->before_dol_mode = CMB_ERR_EXP_RD_MD;
			//}
		}
	}
	return (0);
}

int	ft_exp_excd(t_pars *pars)
{
	//int	exit_code;

	//exit_code = 127;
	pars->temp = ft_strdup(ft_itoa(exit_code));
	return (0);
}

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
		if (!ft_strncmp(str, comp_str, k + 1))
		{
			free(comp_str);
			return (pars->ms_env[i] + k + 2);
		}
		i++;
	}
	return (NULL);
}

int	ft_find_eq(char *env_str)
{
	int	start;

	start = 0;
	//printf("env i = %s\n", env_str);
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
	return(1 + pars->new_exp_decision.exp_read_mode);
	//return (ft_msgerr(ft_getlabel_error_msgs((t_err_msgs)
	//			pars->new_exp_decision.token_type)), 0);
}
