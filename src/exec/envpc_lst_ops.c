#include "../../inc/minishell.h"

t_envp_cpy	*ft_envpcnew(char *var)
{
	t_envp_cpy	*new;

	new = malloc(sizeof(t_envp_cpy));
	if (!new)
		return (NULL);
	new->var = ft_strdup(var);
	new->next = NULL;
	return (new);
}

void	ft_env_varadd_back(t_envp_cpy *envpc_lst, t_envp_cpy *new)
{
	if (!envpc_lst || !new)
		return ;
	while (envpc_lst->next)
	{
		envpc_lst = envpc_lst->next;
	}
	//printf("\n\nENVPC_LAST_LINK IS : %s\n\n", envpc_lst->var);
	envpc_lst->next = new;
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
		free(head);
		head = envpc_lst;
		envpc_lst = envpc_lst->next;
	}
	//free(head->var);
	//free(head);
	return ;
}
