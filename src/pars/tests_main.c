/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/11/29 11:13:30 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code;

int	main(void)
{
	if (ft_tests())
		return (1);
	return (0);
}

int	ft_tests(void)
{
	int			fd;
	char		*user_input;
	//t_hdoc_tab	*hdoc_tab;
	t_shell		shell;

 	ft_bzero(&shell, sizeof(t_shell));
	fd = open("parser.test", O_RDONLY, 644);
	if (fd < 0)
		return (ft_msgerr(ERR_TESTFILE), 1);
	user_input = get_next_line(fd);
	while (user_input)
	{
		shell.retprompt = user_input;
		//ft_read_prompt(user_input, &hdoc_tab);
		ft_read_prompt(&shell);
		free(user_input);
		user_input = get_next_line(fd);
	}
	if (user_input)
	{
		free(user_input);
		user_input = NULL;
	}
	close(fd);
	return (0);
}
