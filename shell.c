/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:42:08 by bgrulois          #+#    #+#             */
/*   Updated: 2022/12/01 10:10:49 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	exit_code;

int	is_valid_history(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

void	fd_closer(t_shell *shell)
{
	shell->cmd = shell->cmd_head;
	while (shell->cmd && shell->cmd->next)
	{
		if (shell->cmd->fd_in > 0)
			close(shell->cmd->fd_in);
		if (shell->cmd->fd_out > 1)
			close(shell->cmd->fd_out);
		shell->cmd = shell->cmd->next;
	}
	if (shell->cmd)
	{
		if (shell->cmd->fd_in > 0)
			close(shell->cmd->fd_in);
		if (shell->cmd->fd_out > 1)
			close(shell->cmd->fd_out);
	}
	return ;
}

void	reset_shell_values(t_shell *shell)
{
	//free_cmd_lst(&shell->cmd);
	fd_closer(shell);
	if (shell->cmd && shell->cmd->cmd)
	{
		free(shell->cmd->cmd);
		shell->cmd->cmd = NULL;
	}		
	ft_lstclear(&shell->cmd, del);
	free_tab(shell->ms_env);
	shell->ms_env = lst_to_envp(shell->envpc);
	clear_envpc_lst(shell->envpc);
	shell->retprompt = NULL;
	free_tab(shell->env_paths);
	shell->env_paths = get_env_paths(shell->ms_env);
	shell->envpc_head = set_env(shell, shell->ms_env);
	ft_unlink_allhdoc(shell->hdoc_tab);
	ft_free_hdoctab(shell->hdoc_tab);
	return ;
}

void	minishell_loop(t_shell *shell)
{
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		shell->retprompt = readline("minishell$> ");
		if (shell->retprompt == NULL)
			break ;
		if (is_valid_history(shell->retprompt))
			add_history(shell->retprompt);
		ft_read_prompt(shell);
		shell->cmd_head = shell->cmd;
		if (shell->cmd_head != NULL && shell->cmd_head->token[0])
		{
			if (shell->cmd && !shell->cmd->next)
				exit_code = simple_exec(shell, shell->ms_env);
			else if (shell->cmd)
				exit_code = pipeline(shell, shell->ms_env);
			if (exit_code == 141)
				exit_code = 0;
		}
		if (shell->retprompt)
			free(shell->retprompt);
		reset_shell_values(shell);
	}
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	if (!isatty(1) || !isatty(0) || !isatty(2))
	{
		write(2, "This shell doesn't handle non-interactive mode, exiting...\n", 60);
		return (-1);
	}
	shell = minishell_init(envp);
	if (!shell)
	{
		write(2, "Init error, exiting\n", 20);
		return (-1);
	}
	minishell_loop(shell);
	ft_exit(1, NULL, shell);
	return (0);
}
