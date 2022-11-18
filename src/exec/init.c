#include "../../inc/minishell.h"

t_shell	*minishell_init(char **envp)
{
	t_shell	*shell;

	(void)envp;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->cmd = NULL;
	shell->cmd_head = NULL;
	shell->env_paths = NULL;
	shell->retprompt = NULL;
	shell->envpc = NULL;
	pipe(shell->pipefd);
	shell->ms_env = NULL;
	shell->env_paths = NULL;
	shell->envpc = NULL;
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
