# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 22:04:39 by mbourgeo          #+#    #+#              #
#    Updated: 2022/10/08 22:09:47 by mbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= common_utils.c \
			ft_split.c \
			ft_strcmp.c

SRCDIR	=	src
LB_PATH	=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJDIR	=	obj
OBJS	=	$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(LB_PATH:.c=.o))
#HDDIR	=	inc

NAME	= libft.a

CC		= gcc
AR		= ar rc
MK		= mkdir -p
RM		= rm -rvf

CFLAGS	 = -Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}

$(OBJDIR)/%.o:	$(SRCDIR)/%.c | $(OBJDIR)
				${CC} ${CFLAGS} -c $< -o $@

$(OBJDIR):
			@${MK} $@

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
