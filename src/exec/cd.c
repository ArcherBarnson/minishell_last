/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 12:12:14 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 16:03:49 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

char	*ft_strdup_offset(char *str, int offset)
{
	int	size;
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
	int	i;

	i = 0;
	home = NULL;
	while (envp[i] && ft_strccmp("HOME=", envp[i], '=') != 0)
		i++;
	if (envp[i] != NULL)
		home = ft_strdup_offset(envp[i], 4);
	return (home);
}

void	update_oldpwd(char **envp, t_envp_cpy *envpc_lst)
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
	export(2, export_cwd, envp, envpc_lst);
	free(export_cwd[1]);
	free(export_cwd);
}

int	cd(int ac, char **path, char **envp, t_envp_cpy *envpc_lst)
{
	char	*home;

	home = get_home_path(envp);
	if (ac == 1)
	{
		if (home == NULL)
		{
			write(2, "cd : HOME not set\n", 19);
			return (1);
		}
		update_oldpwd(envp, envpc_lst);
		chdir(home);
		free(home);
		return (0);
	}
	if (ac > 2)
	{
		free(home);
		write(1, "Wrong number of arguments\n", 27);
		return (1);
	}
	free(home);
	update_oldpwd(envp, envpc_lst);
	chdir(path[1]);
	return (0);
}
