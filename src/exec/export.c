/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:26:22 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/29 21:14:57 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exportcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] == '=' || s2[i] == '=')
			break ;
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '=' && !(s2[i]))
		return (1);
	if (s2[i] == '=' && !(s1[i]))
		return (1);
	return (s1[i] - s2[i]);
}

char	*save_env_var(char *var)
{
	int			i;
	int			j;
	char		*save;

	i = -1;
	j = 0;
	while (var[++i] != '=')
		;
	i++;
	j = i;
	while (var[j])
		j++;
	save = malloc(sizeof(char) * j);
	if (!save)
		return (NULL);
	j = 0;
	while (var[i])
	{
		save[j] = var[i];
		i++;
		j++;
	}
	save[i - 3] = '\0';
	return (save);
}

void	append_var(char *var, char *env_var_buf, t_envp_cpy *envpc_lst)
{
	char	*var_buf;
	char	*appended_var;

	var_buf = NULL;
	appended_var = NULL;
	var_buf = save_env_var(var);
	appended_var = ft_strjoin(env_var_buf, var_buf);
	free(var_buf);
	free(envpc_lst->var);
	envpc_lst->var = ft_strdup(appended_var);
	free(appended_var);
}

void	mod_env_var(char *var, t_envp_cpy *envpc_lst, int mode)
{
	char	*env_var_buf;

	while (envpc_lst->next && (ft_strccmp(var, envpc_lst->var, '=') != 0
			|| ft_strncmp(var, envpc_lst->var, ft_strlen(envpc_lst->var)
				&& var[ft_strlen(envpc_lst->var) - 1])))
		envpc_lst = envpc_lst->next;
	env_var_buf = ft_strdup(envpc_lst->var);
	if (mode == 1)
	{
		free(envpc_lst->var);
		envpc_lst->var = ft_strdup(var);
	}
	if (mode == 2)
		append_var(var, env_var_buf, envpc_lst);
	free(env_var_buf);
	return ;
}

int	export(t_shell *shell, char **av, char **envpc, t_envp_cpy *envpc_lst)
{
	int			i;
	int			mode;
	char		*tmp;

	i = 1;
	if (get_tab_size(av) == 1)
		return (export_no_args(shell, envpc_lst));
	while (i < get_tab_size(av))
	{
		mode = is_valid_string(av[i]);
		if (mode == 1 || mode == 2)
		{
			if (env_var_exists(av[i], envpc, mode))
				mod_env_var(av[i], envpc_lst, mode);
			else
			{
				tmp = ft_strdup(av[i]);
				ft_env_varadd_back(envpc_lst,
					ft_envpcnew(tmp));
				free(tmp);
			}
		}
		i++;
	}
	return (0);
}
