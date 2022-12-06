# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 20:52:12 by bgrulois          #+#    #+#              #
#    Updated: 2022/12/06 12:48:07 by jtaravel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL	=	all

PARSRCS		=	common_core.c common_core_2.c common_core_3.c common_core_4.c \
				common_core_5.c common_initializations_2.c \
				common_memory.c common_error.c common_ascii.c \
				common_labels.c common_labels_2.c common_labels_3.c \
				common_initializations.c \
				lexer_list.c parser_list.c \
				lexer_init_decisions.c lexer_init_decisions_2.c \
				lexer_apply_decision.c \
				lexer_actions.c lexer_actions_2.c \
				parser_actions.c parser_actions_2.c parser_actions_3.c \
				parser_init_decisions.c parser_init_decisions_2.c \
				parser_apply_decision.c \
				expander_init_decisions.c expander_init_decisions_2.c \
				expander_apply_decisions.c \
				expander_actions.c expander_actions_2.c expander_actions_3.c \
				expander_actions_4.c expander_actions_5.c \
				redirector_init_decisions.c redirector_apply_decisions.c \
				redirector_actions.c redirector_actions_2.c redirector_actions_3.c \
				redirector_file_manager.c \
				redirector_heredoc.c redirector_heredoc_2.c redirector_heredoc_3.c \
				redirector_heredoc_4.c redirector_heredoc_5.c \
				transformer_list.c reset_hd.c \

EXSRCS		=	init_utils.c init.c  memory_tools_utils.c memory_tools.c  misc.c \
				pathfinding.c exec_utils.c exit_utils.c exit.c wait.c \
				export_utils.c cd_utils.c cd.c echo.c pwd.c env.c \
				export_no_args.c export.c unset.c builtins_ctl.c \
				envpc_lst_ops.c env_handler.c \
				signals.c exec.c main.c

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
LIB1_NAME	=	lib/gnl/libgnl.a
LIB2_DIR	=	lib/libft
LIB2_NAME	=	lib/libft/libft.a
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
