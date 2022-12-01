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

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = (long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = (long)-n;
		if (n == -2147483648)
		{
			write (fd, "2147483648", 10);
			return ;
		}
	}
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	c = nb % 10 + '0';
	write(fd, &c, 1);
}

//faire same pour shlvl]
void	add_pwd(t_envp_cpy **lst)
{
	char	*cwd;
	t_envp_cpy *tmp;
	char	*tmp2;
	int		sh;

	tmp = *lst;
	if (tmp)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->var , "PWD", 3) == 0)
			{
				cwd = NULL;
				cwd = getcwd(cwd, 0); // can crash
				tmp2 = ft_strjoin("PWD=", cwd);
				free(tmp->var);
				tmp->var = ft_strdup(tmp2);
				free(tmp2);
			}
			if (ft_strncmp(tmp->var , "SHLVL", 5) == 0)
			{
				tmp2 = ft_strdup(tmp->var + 6);
				sh = ft_atoll(tmp2) + 1;
				if (sh > 999)
				{
					write(2, "minishell: warning: shell level ", 32);
					ft_putnbr_fd(sh, 2);
					write(2, " too high, resetting to 1\n", 26);
					sh = 1;
				}
				else if (sh < 0)
					sh = 0;
				free(tmp2);
				tmp2 = ft_itoa(sh);
				free(tmp->var);
				tmp->var = ft_strjoin("SHLVL=", tmp2);
				free(tmp2);
			}
			tmp = tmp->next;
		}
		lst = &tmp;
		free(cwd);
	}
	else if (!(*lst))
	{
		cwd = NULL;
		cwd = getcwd(cwd, 0); // can crash
		tmp2 = ft_strjoin("PWD=", cwd);
		ft_env_varadd_back(lst,
			ft_envpcnew(tmp2));
		free(tmp2);
		tmp2 = ft_strdup("SHLVL=1");
		ft_env_varadd_back(lst,
		ft_envpcnew(tmp2));
		free(tmp2);
	}
	// free(tmp);
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
