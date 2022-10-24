#include "../../inc/minishell.h"

t_envp_cpy	ft_envpcnew(void)
{
	t_envp_cpy	*new;

	new = malloc(sizeof(t_envp_cpy));
	if (!new)
		return (NULL);
	new->var = NULL;
	new->next = NULL;
	return (new);
}

void	ft_env_varadd_back(t_envp_cpy **envpc_lst, t_envp_cpy *new)
{
	t_envp_cpy	*last;

	last = NULL;
	if (!envpc_lst || !new)
		return ;
	new = *envpc_lst;
	if (!new)
	{
		*envpc_lst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
	return ;
}

void	clear_envpc_lst(t_envp_cpy *envpc_lst)
{
	t_envp_cpy	*head;

	if (!envpc_lst)
		return ;
	head = envpc_lst;
	envpc_lst = envpc_lst->next;
	while (envpc_lst->next)
	{
		free(head->var);
		free(envpc->var);
		free(head);
		head = envpc_lst;
		envpc_lst = envpc_lst->next;
	}
	free(envpc_lst->var);
	free(envpc_lst);
	free(head->var);
	free(head);
	return ;
}
