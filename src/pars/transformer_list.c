/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformer_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 00:13:45 by mbourgeo         ###   ########.fr       */
/*   Updated: 2022/09/30 16:01:12 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_new_cmd(char **token)
{
	t_cmd	*new;

	if (ft_mallocator(&new, sizeof(t_cmd)))
		return (0);
	new->token = token;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_cmd	*ft_cmd_addnext(t_cmd *current, t_cmd *next)
{
	if (!current)
		return (current = next, current);
	else if (!next)
		return (ft_msgerr(ERR_NULLCMD), NULL);
	else
	{
		next->prev = current;
		current->next = next;
	}
	return (next);
}

char	**ft_token_list_to_tab(t_command *command)
{
	int		i;
	char	**temp;
	t_token	*token_temp;

	i = 0;
	temp = malloc((command->nb_of_tokens + 1) * sizeof(char *));
	if (!temp)
		return (NULL);
	while (i++ < command->nb_of_tokens)
	{
		temp[i - 1] = ft_strndup(command->token->id, 0);
		free(command->token->id);
		token_temp = command->token;
		command->token = command->token->next;
		free(token_temp);
	}
	temp[i - 1] = 0;
	return (temp);
}

int	ft_free_cmdlist(t_cmd *cmd)
{
	t_cmd	*temp;

	while (1)
	{
		temp = cmd;
		cmd = cmd->next;
		ft_free_tokentab(temp->token, temp->nb_of_tokens);
		free(temp);
		temp = NULL;
		if (cmd == NULL)
			break ;
	}
	cmd = NULL;
	return (0);
}

int	ft_free_tokentab(char **token, int len)
{
	int	i;

	i = 0;
	while (i++ < len)
	{
		free(token[i - 1]);
		token[i - 1] = NULL;
	}
	free(token[i - 1]);
	token[i - 1] = NULL;
	free(token);
	return (0);
}
