/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:36:27 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/01 23:41:37 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_modif_env(char *var, char *tmp2, char *cwd, int sh)
{
	if (ft_strncmp(var, "PWD", 3) == 0)
	{
		cwd = NULL;
		cwd = getcwd(cwd, 0);
		tmp2 = ft_strjoin("PWD=", cwd);
		free(var);
		var = ft_strdup(tmp2);
		free(tmp2);
	}
	if (ft_strncmp(var, "SHLVL", 5) == 0)
		ft_shlvl(var, tmp2, sh);
}

void	ft_pas_d_env(char *cwd, char *tmp2, t_envp_cpy **lst)
{
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	tmp2 = ft_strjoin("PWD=", cwd);
	ft_env_varadd_back(lst,
		ft_envpcnew(tmp2));
	free(tmp2);
	tmp2 = ft_strdup("SHLVL=1");
	ft_env_varadd_back(lst,
		ft_envpcnew(tmp2));
	free(tmp2);
}

void	add_pwd(t_envp_cpy **lst)
{
	char		*cwd;
	t_envp_cpy	*tmp;
	char		*tmp2;
	int			sh;

	tmp = *lst;
	tmp2 = NULL;
	cwd = NULL;
	sh = 0;
	if (tmp)
	{
		while (tmp)
		{
			ft_modif_env(tmp->var, tmp2, cwd, sh);
			tmp = tmp->next;
		}
		lst = &tmp;
		free(cwd);
	}
	else if (!(*lst))
		ft_pas_d_env(cwd, tmp2, lst);
}

void	minishell_assign(t_shell *shell, char **envp)
{
	shell->ms_env = dup_tab(envp);
	shell->env_paths = get_env_paths(envp);
	shell->envpc_head = set_env(shell, shell->ms_env);
	add_pwd(&(shell->envpc));
	free_tab(shell->ms_env);
	shell->ms_env = lst_to_envp(shell->envpc);
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
	minishell_assign(shell, envp);
	return (shell);
}
