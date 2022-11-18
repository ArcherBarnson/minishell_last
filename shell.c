/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:42:08 by bgrulois          #+#    #+#             */
/*   Updated: 2022/10/24 13:58:32 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	exit_code;

int	is_valid_history(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

t_envp_cpy	*set_env(t_shell *shell, char **envp)
{
	if (shell->ms_env == NULL)
		shell->envpc = envp_to_lst(envp);
	else
		shell->envpc = envp_to_lst(shell->ms_env);
	return (shell->envpc);
}

int	start_shell(t_shell *shell, char **envp)
{
	t_hdoc_tab	*hdoc_tab;

	hdoc_tab = NULL;
	shell->ms_env = NULL;
	shell->env_paths = get_env_paths(envp);		//call again if env builtins are used
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		shell->envpc_head = set_env(shell, envp);
		shell->retprompt = readline("minishell#> ");
		if (shell->retprompt == NULL)
			break ;
		if (is_valid_history(shell->retprompt))
			add_history(shell->retprompt);
		shell->cmd = ft_read_prompt(shell->retprompt, &hdoc_tab);
		shell->cmd_head = shell->cmd;
		printf("exit_status = %i\n", exit_code);
		if (shell->cmd_head != NULL)
		{
			if (!shell->cmd->next)
				exit_code = simple_exec(shell, shell->ms_env);
			else
				exit_code = pipeline(shell, shell->ms_env);
			if (shell->retprompt)
				bzero(shell->retprompt,
					ft_strlen(shell->retprompt));
			free_cmd_lst(shell->cmd);
			shell->ms_env = lst_to_envp(shell->envpc);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = minishell_init(envp);
	if (!shell)
	{
		write(2, "Init error, exiting\n", 20);
		return (-1);
	}
	start_shell(shell, envp);
	free_all(shell);					//doesnt exist
	return (0);
}
