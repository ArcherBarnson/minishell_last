/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:33:55 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/28 12:42:22 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_cmd	*ft_read_prompt(char *user_input, t_hdoc_tab **hdoc_tab)

int	ft_read_prompt(t_shell *shell)
{
	t_lex		lex;
	t_pars		pars;

	ft_bzero(&lex, sizeof(t_lex));
	ft_bzero(&pars, sizeof(t_pars));
	pars.pars_env = shell->envpc;
	ft_general_initialize(&lex, &pars);
	//lex.user_input = user_input;
	lex.user_input = shell->retprompt;
	lex.user_input_2 = shell->retprompt;
	//printf("check shell->retprompt : %s\n", lex.user_input);
	//printf("\n--------------------------\n");
	//printf("\033[0;32m%s\033[0m", lex.user_input);
	if (ft_around_lexer(&lex))// || ft_print_debug_content(&lex, &pars, "lex"))
		return (ft_error_return(&lex, &pars, shell));
	if (ft_around_parser(&lex, &pars))// || ft_print_debug_content(&lex, &pars, "pars"))
		return (ft_error_return(&lex, &pars, shell));
	if (ft_expander(&pars))// || ft_print_debug_content(&lex, &pars, "exp"))
	 	return (ft_error_return(&lex, &pars, shell));
	if (ft_around_redirector(&lex, &pars))// || ft_print_debug_content(&lex, &pars, "redir"))
		return (ft_error_return(&lex, &pars, shell));
	if (ft_transformer(&pars))// || ft_print_debug_content(&lex, &pars, "trans"))
		return (ft_error_return(&lex, &pars, shell));
	//*hdoc_tab = pars.hdoc_tab;
	shell->hdoc_tab = pars.hdoc_tab;
	//printf("pars.cmd_head : %s\n", pars.cmd_head->token[0]);
	//printf("pars.cmd_head : %s\n", pars.cmd_head->cmd);
	pars.cmd = pars.cmd_head;
	shell->cmd = pars.cmd;
	ft_tklist_freeall(&lex);
	shell->pars = &pars;
	//ft_execfree_freeall(&pars);
	ft_pars_freeall(&pars);
	return (0);
}

int	ft_error_return(t_lex *lex, t_pars *pars, t_shell *shell)
{
	(void)pars;
	shell->cmd = NULL;
	printf("return 1 to exec with shell->cmd = NULL\n");
	ft_tklist_freeall(lex);
//	ft_execfree_freeall(pars);
//	ft_pars_freeall(pars);
	return (1);
}

int	ft_around_lexer(t_lex *lex)
{
	if (ft_lexer(lex))
	{
		ft_free_tokenlist(lex->token);
		lex->token = NULL;
		lex->temp = ft_strndup("", 0);
		lex->token = ft_token_addnext(lex->token, ft_new_token(lex->temp));
		lex->nb_of_tokens = 1;
		lex->token->type = lex->new_decision.token_type;
		free(lex->temp);
		lex->temp = NULL;
		return (1);
	}
	return (0);
}

int	ft_around_parser(t_lex *lex, t_pars *pars)
{
	pars->nb_of_commands = 0;
	pars->nb_of_tokens = lex->nb_of_tokens;
	if (ft_parser(lex, pars))
	{
		ft_tklist_freeall(lex);
		ft_pars_freeall(pars);
		return (1);
	}
	return (0);
}

int	ft_around_redirector(t_lex *lex, t_pars *pars)
{
	if (ft_redirector(pars))
	{
		ft_tklist_freeall(lex);
		ft_pars_freeall(pars);
		return (1);
	}
	return (0);
}

int	ft_real_pars(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '|')
			c++;
		i++;
	}
	return (c);
}

int	ft_lexer(t_lex *lex)
{
	int	ret;

	//lex->nb_tcmd = ft_real_pars(lex->user_input);
	ret = ft_check_forbidden_cmb(lex->user_input);
	while (*lex->user_input && *lex->user_input != '\n'
		&& ret == 0)
	{
		ret = ft_lex_apply_decision(lex);
		lex->user_input++;
	}
	if (!ret)
		ret = ft_lex_apply_decision(lex);
	if (lex->token)
		lex->token = lex->token->next;
	if (ret)
		return (ft_msgerr((char *)ft_getlabel_error_msgs_txt
				(ret - 1)));
	else
		return (0);
}

void	check_file_for_segv(t_pars *pars, char *str)
{
	if (open(str, O_RDONLY) == -1)
	{
		write(2, "File: ", 6);
		write(2, str, ft_strlen(str));
		write(2, " does not exit\n", 15);
	}
	pars->cmdsts = 1;
}

void	ft_check_2(t_pars *pars, char **res, char *str)
{
	int	i;

	i = 0;
	while (res[i])
	{
		if (ft_strlen(res[i]) == 1 && res[i][0] == '<')
		{
			free(str);
			check_file_for_segv(pars, res[i + 1]);
		}
		i++;
	}
}
	

void	ft_checker_anti_segv(t_pars *pars, char *str)
{
	int	i;
	char	**res;

	res = ft_split(str, ' ');
	i = 0;
	while (res[i])
		i++;
	if (i >= 2)
		ft_check_2(pars, res, str);
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

int	ft_parser(t_lex *lex, t_pars *pars)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	pars->cmdsts = 0;
	pars->token = lex->token;
	pars->crt_tok_type = pars->token->type;
	ft_checker_anti_segv(pars, lex->user_input_2);
	while (i++ < pars->nb_of_tokens && ret == 0 && !pars->cmdsts)
	{
		ret = ft_pars_apply_decision(pars);
		pars->token = pars->token->next;
		pars->crt_tok_type = pars->token->type;
	}
	if (!ret)
	{
		pars->crt_tok_type = TOK_END_OF_INPUT;
		ret = ft_pars_apply_decision(pars);
	}
	if (pars->command)
	{
		pars->command->token = pars->command->token->next;
		pars->command = pars->command->next;
	}
	if (ret)
		return (ft_msgerr((char *)ft_getlabel_error_msgs_txt
				(ret - 1)));
	return (0);
}

char	*ft_strjoin4(char *s1, char *s2, char *res)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s1[++i])
	{
		res[j] = s1[i];
		j++;
	}
	i = -1;
	while (s2[++i])
	{
		res[j] = s2[i];
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*ft_strjoin3(char *s1, char *s2)
{
	char	*res;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * ((ft_strlen((char *)s1)
					+ ft_strlen((char *)s2)) + 1));
	if (!res)
		return (0);
	res = ft_strjoin4(s1, s2, res);
	free(s1);
	return (res);
}
char	*ft_small_check_exp(t_pars *pars, char *str)
{
	char	**recup;
	int	i;

	i = 0;
	(void)pars;
	recup = ft_split(str, ' ');
	while (recup[i])
	{
		if (ft_strcmp(recup[i], "$?"))
		{
			free(recup[i]);
			recup[i] = ft_itoa(exit_code);
		}
		i++;
	}
	free(str);
	str = ft_strdup("");
	i = 0;
	while (recup[i])
	{
		str = ft_strjoin3(str, recup[i]);
		free(recup[i]);
		i++;
	}
	free(recup);
	return (str);
}

void	ft_remake_parsing(t_pars *pars);

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*new_str_space(char *str)
{
	char	*res;

	int	i;
	int	c;
	int	j;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '$')
			c++;
		i++;
	}
	res = malloc(sizeof(char) * (ft_strlen(str) + c + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			res[j] = ' ';
			j++;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = 0;
	free(str);
	return (res);
}

char	*ft_big_exp(t_pars *pars, char *str)
{
	t_envp_cpy *tmp;
	char	**recup;
	int	i = 0;

	str = new_str_space(str);
	recup = ft_split(str, ' ');

	while (recup[i])
	{
		tmp = pars->pars_env;
		while (tmp->next)
		{
			if (ft_strncmp(recup[i] + 1, tmp->var, ft_strlen(recup[i] + 1)) == 0 && ft_strlen(recup[i]) > 1)
			{
				free(recup[i]);
				recup[i] = ft_strdup(tmp->var + check_equal(tmp->var));
			}
			tmp = tmp->next;
		}
		i++;
	}
	free(str);
	str = ft_strdup("");
	i = 0;
	while (recup[i])
	{
		str = ft_strjoin3(str, recup[i]);
		free(recup[i]);
		i++;
	}
	free(recup);
	return (str);
}

int	ft_expander(t_pars *pars)
{
	int		i;
	int		j;
	int		ret;
	char	*temp;

	i = 0;
	j = 0;
	ret = 0;
	while (i++ < pars->nb_of_commands)
	{
		while (j++ < pars->command->nb_of_tokens)
		{
			pars->token = pars->command->token;
			ft_init_expander(pars);
			pars->before_dol_mode = 0;
			pars->parser_text = ft_strndup(pars->token->id, 0);
			temp = pars->parser_text;
			ret = ft_inner_loop_expander(pars);
			pars->command->token->id = ft_small_check_exp(pars, pars->command->token->id);
			pars->command->token->id = ft_big_exp(pars, pars->command->token->id);
			free(temp);
			if (ret)
				return (ret);
			pars->command->token = pars->command->token->next;
			ft_init_expander(pars);
		}
		pars->command = pars->command->next;
		j = 0;
	}
	return (0);
}

void	check_sq_dq(t_pars *pars, char c)
{
	if (c == '\'' && pars->dq_opened == 0)
	{
		if (pars->sq_opened == 0)
			pars->sq_opened = 1;
		else
			pars->sq_opened = 0;
	}
	if (c == '"' && pars->sq_opened == 0)
	{
		if (pars->dq_opened == 0)
			pars->dq_opened = 1;
		else
			pars->dq_opened = 0;
	}
}

static char	*cut_sds(char *str, t_pars *pars, int i, int c)
{
	int	j;

	j = i - 1;
	if (c == 1)
	{
		if (pars->sq_opened)
			pars->sq_opened = 0;
		else
			pars->sq_opened = 1;
		while (str[++j])
			str[j] = str[j + 1];
	}
	if (c == 2)
	{
		if (pars->dq_opened)
			pars->dq_opened = 0;
		else
			pars->dq_opened = 1;
		while (str[++j])
			str[j] = str[j + 1];
	}
	str[j] = 0;
	return (str);
}

void	ft_remake_parsing(t_pars *pars)
{
	int	i;

	i = -1;
	while (pars->command->token->id[++i])
	{
		if (pars->command->token->id[i] == '\'' && pars->dq_opened == 0)
		{
			pars->command->token->id = cut_sds(pars->command->token->id, pars, i, 1);
			i--;
		}
		else if (pars->command->token->id[i] == '"' && pars->sq_opened == 0)
		{
			pars->command->token->id = cut_sds(pars->command->token->id, pars, i, 2);
			i--;
		}
	}
}

int	ft_inner_loop_expander(t_pars *pars)
{
	int	ret;

	ret = 0;
	while (1)
	{
		//printf("checking token->type : %d\n", pars->token->type);
		ft_remake_parsing(pars);
		//if (pars->token->type == TOK_WORD)
		//	ret = ft_exp_apply_decision(pars);
		if (pars->parser_text[0] == '\0')
			break ;
		pars->parser_text++;
		pars->offset_start++;
	}
	if (ret)
		return (ft_msgerr((char *)ft_getlabel_error_msgs_txt
				(ret - 1)));
	return (0);
}

int	ft_redirector(t_pars *pars)
{
	int		i;
	int		j;
	int		k;
	int		count;
	int		ret;

	i = 0;
	j = 0;
	count = 0;
	ret = 0;
	ft_init_redir_decisions(pars);
	ft_init_redir_actions(pars);
	while (i++ < pars->nb_of_commands)
	{
		k = pars->command->nb_of_tokens;
		while (j++ < k)
		{
			pars->token = pars->command->token;
			ret = ft_redir_apply_decision(pars);
			if (ret)
				return (ret);
			pars->command->token = pars->command->token->next;
		}
		pars->command = pars->command->next;
		count += pars->command->nb_of_tokens;
		j = 0;
	}
	return (0);
}

int	ft_transformer(t_pars *pars)
{
	int		i;

	i = 0;
	while (i++ < pars->nb_of_commands)
	{
		pars->cmd = ft_cmd_addnext(pars->cmd,
				ft_new_cmd(ft_token_list_to_tab(pars->command)));
		if (i == 1)
			pars->cmd_head = pars->cmd;
		pars->cmd->id = pars->command->id;
		pars->cmd->nb_of_tokens = pars->command->nb_of_tokens;
		pars->cmd->fd_in = pars->command->fd_in;
		pars->cmd->fd_out = pars->command->fd_out;
		pars->command = pars->command->next;
	}
	pars->hdoc_tab = ft_hdoc_list_to_tab(pars->hdoc_list,
			ft_count_list(pars->hdoc_list));
	pars->cmd = pars->cmd_head;
	return (0);
}
