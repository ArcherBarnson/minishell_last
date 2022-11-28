/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:39:27 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 17:50:47 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h" 

char	*export_format(char *var)
{
	char	*formated_var;

	formated_var = ft_strjoin("export ", var);
	return (formated_var);
}

int	env(int ac, char **av, char **envp, int mode)
{
	int		i;
	char	*export_var;

	i = 0;
	(void)av;
	if (ac != 1 || !envp)
		return (0);
	while (envp[i] != NULL)
	{
		if (is_env_var(envp[i]) && mode == 0)
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		else if (mode == 1)
		{
			export_var = export_format(envp[i]);
			write(1, export_var, ft_strlen(export_var));
			write(1, "\n", 1);
			free(export_var);
		}
		i++;
	}
	return (0);
}
