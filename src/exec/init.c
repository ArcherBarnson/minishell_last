#include "../../inc/minishell.h"

void	minishell_assign(t_shell *shell, char **envp)
{
	shell->ms_env = dup_tab(envp);
	if (shell->ms_env[0] == NULL)
		shell->ms_env = build_minimal_env();
	pipe(shell->pipefd);
	shell->env_paths = get_env_paths(envp);
	shell->envpc_head = set_env(shell, shell->ms_env);
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
	//shell->pipefd = NULL;
	//pipe(shell->pipefd);
	shell->ms_env = NULL;
	shell->envpc = NULL;
	shell->pars = NULL;
	minishell_assign(shell, envp);
	/*if (!shell->envpc)
	{
		free(shell);
		return (NULL);
	}*/
	/*if (pipe(shell->pipefd) == -1)
	{
		//free_lst(shell->envp);		//fct doesnt exist
		free(shell);
		return (NULL);
	}*/
	return (shell);
}
