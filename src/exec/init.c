/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:36:27 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 14:37:15 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//faire same pour shlvl]
void	add_pwd(t_envp_cpy **lst)
{
	char	*cwd;
	char	*tmp;

	cwd = NULL;
	cwd = getcwd(cwd, 0); // can crash
	tmp = ft_strjoin("PWD=", cwd);
	free(cwd);
	// tmp = NULL ???
	if (!(*lst))
	{
		ft_env_varadd_back(lst,
			ft_envpcnew(tmp));
	}
	free(tmp);
}

void	minishell_assign(t_shell *shell, char **envp)
{
	shell->ms_env = dup_tab(envp);
	printf("ms_env = %p\n", shell->ms_env);
	//if (shell->ms_env[0] == NULL)
	//	shell->ms_env = build_minimal_env();
	shell->env_paths = get_env_paths(envp);
	shell->envpc_head = set_env(shell, shell->ms_env);
	printf("list = %p\n", shell->envpc_head);
	add_pwd(&(shell->envpc_head));
	//add_shlvl
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
	minishell_assign(shell, envp);
	return (shell);
}
