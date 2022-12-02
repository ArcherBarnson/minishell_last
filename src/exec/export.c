/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:26:22 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/02 17:42:05 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*save_env_var(char *var)
{
	int			i;
	int			j;
	char		*save;

	i = -1;
	j = 0;
	while (var[++i] != '+')
		;
	i += 2;
	while (var[i + j])
		j++;
	save = malloc(sizeof(char) * (j + 1));
	if (!save)
		return (NULL);
	j = 0;
	while (var[i + j])
	{
		save[j] = var[i + j];
		j++;
	}
	save[j] = '\0';
	return (save);
}

void	append_var(char *var, char *env_var_buf, t_envp_cpy *envpc_lst)
{
	char	*var_buf;
	char	*appended_var;
	char	*tmp;

	var_buf = NULL;
	appended_var = NULL;
	var_buf = save_env_var(var);
	if (check_if_equal(env_var_buf))
		appended_var = ft_strjoin(env_var_buf, var_buf);
	else
	{
		tmp = ft_strjoin(env_var_buf, "=");
		appended_var = ft_strjoin(tmp, var_buf);
		free(tmp);
	}
	free(var_buf);
	free(envpc_lst->var);
	envpc_lst->var = ft_strdup(appended_var);
	free(appended_var);
}

void	mod_env_var(char *var, t_envp_cpy *envpc_lst, int mode)
{
	char	*env_var_buf;

	while (envpc_lst && !ft_exportcmp(envpc_lst->var, var))
		envpc_lst = envpc_lst->next;
	env_var_buf = ft_strdup(envpc_lst->var);
	if (mode == 1)
	{
		if (check_if_equal(var))
		{
			free(envpc_lst->var);
			envpc_lst->var = ft_strdup(var);
		}	
	}
	if (mode == 2)
	{
		append_var(var, env_var_buf, envpc_lst);
	}
	free(env_var_buf);
	return ;
}

int	env_var_exists_export(char *str, t_envp_cpy *envpc)
{
	if (!str || !envpc)
		return (0);
	while (envpc)
	{
		if (ft_exportcmp(str, envpc->var))
			return (1);
		envpc = envpc->next;
	}
	return (0);
}

int	export(t_shell *shell, char **av, t_envp_cpy **envpc_lst)
{
	int			i;
	int			mode;
	char		*tmp;

	i = 1;
	if (get_tab_size(av) == 1)
		return (export_no_args(shell, *envpc_lst));
	while (i < get_tab_size(av))
	{
		mode = is_valid_string(av[i]);
		if (mode)
		{
			if (*envpc_lst && env_var_exists_export(av[i], *envpc_lst))
				mod_env_var(av[i], *envpc_lst, mode);
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
