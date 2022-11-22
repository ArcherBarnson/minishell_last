/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:58:17 by bgrulois          #+#    #+#             */
/*   Updated: 2022/11/22 10:34:08 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	strcmp_diff(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}
/*
char	**export_no_args(t_envp_cpy *envpc_lst, char **envpc)
{
	char	**sorted_envpc;
	char	**envpc;
	int	i;
	int	j;

	i = 0;
	j = -1;
	sorted_envpc = malloc(sizeof(char *) * get_envp_lst_size(envpc_lst) + 1);
	if (!sorted_envpc)
		return ;
	envpc = lst_to_envp(envpc_lst);
	while (envpc[++j])
	{
		while (strcmp_diff(envpc[i], envpc[j]) == 0)
			i++;
	}
}
*/
