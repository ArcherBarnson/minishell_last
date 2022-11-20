/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:46:53 by mbourgeo          #+#    #+#             */
/*   Updated: 2021/12/23 01:11:35 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/* ************************************************************************** */
/*                             common_utils.c                                 */
/* ************************************************************************** */
size_t  ft_strlen(const char *s);
char    *ft_strdup(const char *s);
char    *ft_strndup(const char *s, size_t n);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_substr(char const *s, unsigned int start, size_t len);
int     ft_getsize(int n);
char    *ft_itoa(int n);

/* ************************************************************************** */
/*                               ft_split.c                                   */
/* ************************************************************************** */
char    **ft_split(char const *s, char c);

/* ************************************************************************** */
/*                                ft_strcmp.c                                 */
/* ************************************************************************** */
int     ft_strcmp(char *s1, char *s2);

#endif
