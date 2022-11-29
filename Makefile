# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 18:34:29 by mbourgeo          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/11/29 20:26:23 by mbourgeo         ###   ########.fr        #
=======
#    Updated: 2022/11/29 20:20:17 by bgrulois         ###   ########.fr        #
>>>>>>> 7f6f80a4170491d52272adb027bcedab75bf0bd0
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	=	all

PARSRCS		=	common_core.c common_initializations.c common_memory.c \
				common_error.c common_labels.c \
				common_ascii.c common_debug.c \
				lexer_list.c parser_list.c \
				lexer_init_decisions.c lexer_apply_decision.c lexer_actions.c \
				parser_init_decisions.c parser_apply_decision.c parser_actions.c \
				expander_init_decisions.c expander_apply_decisions.c expander_actions.c \
				redirector_init_decisions.c redirector_apply_decisions.c redirector_actions.c \
				redirector_file_manager.c redirector_heredoc.c \
				transformer_list.c \
				#tests_main.c
EXSRCS		=	init.c  memory_tools.c  misc.c  pathfinding.c exec_utils.c \
				exit.c wait.c export_utils.c cd.c echo.c pwd.c env.c \
				export_no_args.c export.c unset.c builtins_ctl.c \
				envpc_lst_ops.c env_handler.c \
				signals.c exec.c ../../shell.c #../../builtins/*.c\

PARSRCDIR	=	src/pars
PARPATH		=	$(addprefix $(PARSRCDIR)/, $(PARSRCS))
OBJDIR		=	obj
PAROBJS		=	$(patsubst $(PARSRCDIR)/%, $(OBJDIR)/%, $(PARPATH:.c=.o))
EXSRCDIR	=	src/exec
EXPATH		=	$(addprefix $(EXSRCDIR)/, $(EXSRCS))
EXOBJS		=	$(patsubst $(EXSRCDIR)/%, $(OBJDIR)/%, $(EXPATH:.c=.o))
OBJS		=	$(PAROBJS) $(EXOBJS)

DEPDIR		=	dep
PARDEP		=	$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(PAROBJS))
EXDEP		=	$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/%.d, $(EXOBJS))
DEP			=	$(PARDEP) $(EXDEP)

#HDSRCS	=	minishell.h
HDDIR		=	inc
HDPATH	=	$(addprefix $(HDDIR)/, $(HDSRCS))

NAME		=	minishell
LIB1_DIR	=	lib/gnl
LIB1_NAME	=	libgnl.a
LIB2_DIR	=	lib/libft
LIB2_NAME	=	libft.a
HDLIB1_DIR	=	$(LIB1_DIR)/inc
HDLIB2_DIR	=	$(LIB2_DIR)/inc
CC			=	gcc
RM			=	rm -f
RMD			=	rm -rvf
MK			=	mkdir -p
#DEBUG		=	-g -fsanitize=address
#DEBUG		=	-g -fsanitize=thread
DEBUG		=	-g3
CFLAGS		=	-Wall -Wextra -Werror
LFLAGS		=	-lreadline
DFLAGS		=	-MMD -MF
#################################

all:		$(NAME)

$(NAME):	$(OBJS) | $(LIB1_NAME) Makefile $(LIB2_NAME) Makefile
				$(CC) $(CFLAGS) $(DEBUG) $^ -I$(MD_HD_DIR) -I$(HDLIB1_DIR) -L$(LIB1_DIR) -lgnl -I$(HDLIB2_DIR) -L$(LIB2_DIR) -lft $(LFLAGS) -o $@

$(LIB1_NAME):
				$(MAKE) -C $(LIB1_DIR) all

$(LIB2_NAME):
				$(MAKE) -C $(LIB2_DIR) all

-include $(DEP)
$(OBJDIR)/%.o:		$(PARSRCDIR)/%.c | $(LIB1_NAME) $(LIB1_NAME) $(OBJDIR) $(DEPDIR) $(HDPATH)
							$(CC) $(CFLAGS) $(DEBUG) $(DFLAGS) $(DEPDIR)/$*.d -I$(HDDIR) -I$(HDLIB1_DIR) -I$(HDLIB2_DIR) -c $< -o $@

-include $(DEP)
$(OBJDIR)/%.o:		$(EXSRCDIR)/%.c | $(LIB1_NAME) $(LIB1_NAME) $(OBJDIR) $(DEPDIR) $(HDPATH)
							$(CC) $(CFLAGS) $(DEBUG) $(DFLAGS) $(DEPDIR)/$*.d -I$(HDDIR) -I$(HDLIB1_DIR) -I$(HDLIB2_DIR) -c $< -o $@

$(OBJDIR) $(DEPDIR):		;
				@$(MK) $@

clean:		;
				@$(RMD) $(OBJDIR) $(DEPDIR)
				$(MAKE) -C $(LIB1_DIR) fclean
				$(MAKE) -C $(LIB2_DIR) fclean

fclean:		clean
				@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
