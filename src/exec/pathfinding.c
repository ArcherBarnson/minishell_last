/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:20:11 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 13:18:46 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_env_paths(char **envp)
{
	int			i;
	char		*path_var;
	char		**paths;

	paths = NULL;
	path_var = NULL;
	i = 0;
	if (!envp || !envp[i])
		return (NULL);
	while (envp[i] != NULL
		&& ft_strncmp((const char *)envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path_var = ft_strdup(envp[i]);
	paths = ft_split(path_var + 5, ':');
	free(path_var);
	return (paths);
}

char	*find_path(char *cmd, char **env_paths)
{
	int			i;
	char		*tmp;
	char		*path;

	i = -1;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (access((const char *)cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!env_paths || !env_paths[0])
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
		return (NULL);
	while (env_paths[++i])
	{
		path = ft_strjoin(env_paths[i], "/");
		tmp = ft_strdup(path);
		free(path);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access((const char *)path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}
