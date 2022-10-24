/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <mbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:23:23 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/08/15 21:45:26 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		ft_read_buffer(int fd, char **stock);
char	*ft_update_stock(char **stock, int stock_size, int index_nl);
char	*ft_mem_alloc(int n);
int		ft_strlen2(const char *s);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_substr2(char **s, int start, int len);
int		ft_index_nl(char *str);

#endif
