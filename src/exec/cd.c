/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:12:14 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 13:23:21 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

void	ft_on_envoi(char **export_cwd, char *cwd, t_shell *shell,
		t_envp_cpy **envpc_lst)
{
	export_cwd[0] = ft_strdup("export");
	export_cwd[1] = ft_strjoin("OLDPWD=", cwd);
	export_cwd[2] = NULL;
	export(shell, export_cwd, envpc_lst);
	free(export_cwd[0]);
	free(export_cwd[1]);
	free(export_cwd);
	free(cwd);
}

void	update_oldpwd(t_shell *shell, t_envp_cpy **envpc_lst)
{
	char		*cwd;
	char		**export_cwd;
	t_envp_cpy	*tmp;

	export_cwd = malloc(sizeof(char *) * 3);
	if (!export_cwd)
		return ;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		tmp = *envpc_lst;
		while (tmp->next)
		{
			if (ft_strncmp(tmp->var, "PWD=", 4) == 0)
				cwd = ft_strdup(tmp->var + 4);
			tmp = tmp->next;
		}
	}
	ft_on_envoi(export_cwd, cwd, shell, envpc_lst);
}

void	update_pwd(t_shell *shell, t_envp_cpy **envpc_lst)
{
	char	*cwd;
	char	**export_cwd;

	export_cwd = malloc(sizeof(char *) * 3);
	if (!export_cwd)
		return ;
	cwd = getcwd(NULL, 0);
	export_cwd[0] = ft_strdup("export");
	export_cwd[1] = ft_strjoin("PWD=", cwd);
	export_cwd[2] = NULL;
	export(shell, export_cwd, envpc_lst);
	free(export_cwd[0]);
	free(export_cwd[1]);
	free(export_cwd);
	free(cwd);
}

void	ft_check_home(char *home, t_shell *shell, t_envp_cpy **envpc_lst)
{
	if (home == NULL)
	{
		write(2, "cd : HOME not set\n", 19);
		return ;
	}
	update_oldpwd(shell, envpc_lst);
	chdir(home);
	update_pwd(shell, envpc_lst);
	free(home);
	return ;
}

int	cd(t_shell *shell, char **path, char **envp, t_envp_cpy **envpc_lst)
{
	char	*home;

	home = get_home_path(envp);
	if (get_tab_size(shell->cmd->token) == 1)
	{
		ft_check_home(home, shell, envpc_lst);
		return (1);
	}
	if (get_tab_size(shell->cmd->token) > 2)
	{
		free(home);
		write(2, "Wrong number of arguments\n", 27);
		return (1);
	}
	free(home);
	update_oldpwd(shell, envpc_lst);
	if (chdir(path[1]))
	{
		perror("cd ");
		return (1);
	}
	update_pwd(shell, envpc_lst);
	return (0);
}
