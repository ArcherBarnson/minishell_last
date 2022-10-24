/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 00:47:14 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/15 21:46:26 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stock;
	int			index_nl;

	if (!stock)
		stock = ft_mem_alloc(1);
	index_nl = ft_index_nl(stock);
	if (index_nl == -1)
	{
		index_nl = ft_read_buffer(fd, &stock);
		if (index_nl == -1)
		{
			stock = NULL;
			free(stock);
			return (NULL);
		}
	}
	return (ft_update_stock(&stock, ft_strlen2(stock), index_nl));
}

int	ft_read_buffer(int fd, char **stock)
{
	char	*buffer;
	int		index_nl;
	int		nb_char;

	nb_char = BUFFER_SIZE;
	index_nl = -1;
	while (nb_char == BUFFER_SIZE && index_nl == -1)
	{
		buffer = ft_mem_alloc(BUFFER_SIZE + 1);
		nb_char = read(fd, buffer, BUFFER_SIZE);
		if (nb_char == -1)
			break ;
		index_nl = ft_index_nl(buffer);
		*stock = ft_strjoin2(*stock, buffer);
	}
	if (nb_char == -1 || !*stock[0])
	{
		if (nb_char == -1)
			free(buffer);
		free(*stock);
		return (-1);
	}
	return (ft_strlen2(*stock) - (index_nl >= 0) * (nb_char - index_nl));
}

char	*ft_update_stock(char **stock, int stock_size, int index_nl)
{
	char	*new_line;

	new_line = ft_substr2(stock, 0, index_nl + 1);
	*stock = ft_substr2(stock, index_nl + 1, stock_size - index_nl - 1);
	return (new_line);
}
