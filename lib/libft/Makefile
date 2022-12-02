# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 22:04:39 by mbourgeo          #+#    #+#              #
#    Updated: 2022/11/29 04:49:16 by mbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_isalpha.c ft_isdigit.c ft_strlen.c ft_strdup.c ft_strndup.c \
		ft_strncmp.c ft_strjoin.c ft_substr.c ft_getsize.c ft_itoa.c \
		ft_split.c ft_strcmp.c ft_strnstr.c ft_strkchr.c
SRCDIR	=	src
LB_PATH	=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJDIR	=	obj
OBJS	=	$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(LB_PATH:.c=.o))
HDDIR	=	inc

NAME	= libft.a

CC		= gcc
AR		= ar rc
MK		= mkdir -p
RM		= rm -rvf

CFLAGS	 = -Wall -Wextra -Werror -g3

all:		${NAME}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
				${CC} -I${HDDIR} ${CFLAGS} -c $< -o $@

$(OBJDIR):
			@${MK} $@

clean:
			${RM} ${OBJDIR}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
