/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:42:08 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/28 20:03:14 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

//############### DEBUG FUNCTIONS ################################

char 	**file_to_tab(int fd, int size)
{
	char	fileline[size + 1];
	char	**returntab;

	returntab = NULL;
	read(fd, fileline, size);
	fileline[size] = '\0';
	returntab = ft_split(fileline, '\n');
	return (returntab);
}

char	**debug_lst(void)
{
	int	fd_msh;
	int	i = 0;
	char	**msh_tab;
	char	dudbuf[2048];

	fd_msh = open("./test.dbg", O_RDONLY);		//use with caution
	if (fd_msh < 0)
	{
		printf("Fd failure, check your files\n");
		return (NULL);
	}
	while (read(fd_msh, dudbuf, 1) != 0)
		i++;
	close(fd_msh);
	fd_msh = open("./test.dbg", O_RDONLY);		//use with caution
	msh_tab = file_to_tab(fd_msh, i);
	close(fd_msh);
	return (msh_tab);

}
//#################################################################

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

void	reset_shell_values(t_shell *shell)
{
	free_cmd_lst(shell->cmd);
	if (shell->cmd && shell->cmd->cmd)
	{
		free(shell->cmd->cmd);
		shell->cmd->cmd = NULL;
	}
	//ft_lstclear(&shell->cmd, del);
	//ft_execfree_freeall(shell->pars);
	//ft_pars_freeall(shell->pars);
	//free(shell->pars);
	free_tab(shell->ms_env);
	shell->ms_env = lst_to_envp(shell->envpc);
	//ft_envpc_clear(&shell->envpc_head, del);
	clear_envpc_lst(shell->envpc);
	shell->retprompt = NULL;
	free_tab(shell->env_paths);
	shell->env_paths = get_env_paths(shell->ms_env);
	shell->envpc_head = set_env(shell, shell->ms_env);
	return ;
}

void	minishell_loop(t_shell *shell)
{
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		shell->retprompt = readline("$>");
		if (shell->retprompt == NULL)
			break ;
		if (is_valid_history(shell->retprompt))
			add_history(shell->retprompt);
		ft_read_prompt(shell);
		shell->cmd_head = shell->cmd;
		if (shell->cmd_head != NULL)
		{
			if (!shell->cmd->next)
				exit_code = simple_exec(shell, shell->ms_env);
			else
				exit_code = pipeline(shell, shell->ms_env);
		//	printf("---exit_code = %i---\n", exit_code);
			//if (shell->retprompt)
			//	bzero(shell->retprompt,
			//		ft_strlen(shell->retprompt));
		}
		if (shell->retprompt)
			free(shell->retprompt);
		reset_shell_values(shell);
	}
	return ;
}

int	start_shell(t_shell *shell)
{
	minishell_loop(shell);
	//free_tab(shell->env_paths);
	//free(shell->cmd->cmd);
	//shell->env_paths = get_env_paths(shell->ms_env);
	return (0);
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
	start_shell(shell);
	free_all(shell);
	ft_exit(1, NULL);
	return (0);
}
