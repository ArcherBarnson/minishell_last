/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/10/10 22:23:35 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_hdoc_tab	*hdoc_tab;

	fd = open("parser.test", O_RDONLY, 644);
	if (fd < 0)
		return (ft_msgerr(ERR_TESTFILE), 1);
	user_input = get_next_line(fd);
	while (user_input)
	{
		ft_read_prompt(user_input, &hdoc_tab);
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
