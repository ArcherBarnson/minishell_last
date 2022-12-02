/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:36:27 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 19:27:23 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_modif_env(char *var, char *tmp2, char *cwd)
{
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	tmp2 = ft_strjoin("PWD=", cwd);
	free(var);
	var = ft_strdup(tmp2);
	free(cwd);
	free(tmp2);
	return (var);
}

void	add_pwd(t_envp_cpy **lst, int c, int p, char *tmp2)
{
	char		*cwd;
	t_envp_cpy	*tmp;

	tmp = *lst;
	cwd = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "SHLVL", 5) == 0)
		{
			c = 1;
			tmp->var = ft_shlvl(tmp->var, tmp2);
		}
		else if (ft_strncmp(tmp->var, "PWD", 3) == 0)
		{
			p = 1;
			tmp->var = ft_modif_env(tmp->var, tmp2, cwd);
		}
		tmp = tmp->next;
	}
	if ((*lst) && ft_little_add(c, p, lst, tmp2))
		lst = &tmp;
	else if (!(*lst))
		ft_pas_d_env(cwd, tmp2, lst);
}

void	minishell_assign(t_shell *shell, char **envp)
{
	shell->ms_env = dup_tab(envp);
	shell->env_paths = get_env_paths(envp);
	shell->envpc_head = set_env(shell, shell->ms_env);
	add_pwd(&(shell->envpc), 0, 0, NULL);
	free_tab(shell->ms_env);
	shell->ms_env = lst_to_envp(shell->envpc_head);
	return ;
}

t_shell	*minishell_init(char **envp)
{
	t_shell	*shell;

	(void)envp;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->hdoc_tab = NULL;
	shell->cmd = NULL;
	shell->cmd_head = NULL;
	shell->env_paths = NULL;
	shell->retprompt = NULL;
	shell->envpc = NULL;
	shell->envpc_head = NULL;
	shell->ms_env = NULL;
	shell->envpc = NULL;
	shell->pars = NULL;
	shell->hdv = 0;
	minishell_assign(shell, envp);
	return (shell);
}
