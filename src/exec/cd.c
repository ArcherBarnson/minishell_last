/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:12:14 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/29 21:16:30 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

int	ft_strccmp(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] != c && s2[i] != c
		&& s1[i] == s2[i] && s1[i] != '+')
		i++;
	if (s1[i] == s2[i] || (s1[i] == '+' && s2[i] == '='))
		return (0);
	return (1);
}

char	*ft_strdup_offset(char *str, int offset)
{
	int		size;
	char	*returnstr;

	size = 0;
	if (!str)
		return (NULL);
	while (str[offset])
	{
		offset++;
		size++;
	}
	returnstr = malloc(sizeof(char) * (size + 1));
	if (!returnstr)
		return (NULL);
	offset -= size;
	size = 0;
	while (str[++offset])
	{
		returnstr[size] = str[offset];
		size++;
	}
	returnstr[size] = '\0';
	return (returnstr);
}

char	*get_home_path(char **envp)
{
	char	*home;
	int		i;

	i = 0;
	home = NULL;
	while (envp[i] && ft_strccmp("HOME=", envp[i], '=') != 0)
		i++;
	if (envp[i] != NULL)
		home = ft_strdup_offset(envp[i], 4);
	return (home);
}

void	update_oldpwd(t_shell *shell, t_envp_cpy **envpc_lst)
{
	char	cwd[4096];
	char	**export_cwd;

	export_cwd = malloc(sizeof(char *) * 3);
	if (!export_cwd)
		return ;
	getcwd(cwd, 4096);
	export_cwd[0] = NULL;
	export_cwd[1] = ft_strjoin("OLDPWD=", cwd);
	export_cwd[2] = NULL;
	export(shell, export_cwd, envpc_lst);
	free(export_cwd[1]);
	free(export_cwd);
}

int	cd(t_shell *shell, char **path, char **envp, t_envp_cpy **envpc_lst)
{
	char	*home;

	home = get_home_path(envp);
	if (get_tab_size(shell->cmd->token) == 1)
	{
		if (home == NULL)
		{
			write(2, "cd : HOME not set\n", 19);
			return (1);
		}
		update_oldpwd(shell, envpc_lst);
		chdir(home);
		free(home);
		return (0);
	}
	if (get_tab_size(shell->cmd->token) > 2)
	{
		free(home);
		write(2, "Wrong number of arguments\n", 27);
		return (1);
	}
	free(home);
	update_oldpwd(shell, envpc_lst);
	chdir(path[1]);
	return (0);
}
