/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 09:44:25 by mbourgeo          #+#    #+#             */
/*   Updated: 2022/12/06 12:49:00 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <errno.h>
# include "../lib/libft/inc/libft.h"
# include "../lib/gnl/inc/get_next_line.h"

# define CD "cd"
# define ECHO "echo"
# define PWD "pwd"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"
# define EXIT "exit"
# define SIG_INT 130
# define SIG_QUIT 131
# define SIG_ABORT 134
# define BUS_ERR 135
# define SIG_SEGV 139
# define NB_FORBIDDEN 2
# define ERR_MALLOC "Error! Malloc"
# define ERR_NULLTKN "Error! New TOKEN is NULL in list"
# define ERR_NULLCMD "Error! New CMD is NULL in list"
# define ERR_NULLHDOC "Error! New HDOC is NULL"
# define ERR_NAMEHDOC "Error! Filename not found in HDOC_LIST"
# define ERR_EQNOTFOUND "Error! no equal sign in env"
# define ERR_STRNULL "Error! String is NULL"
# define ERR_TESTFILE "Error! Reading file parser.test"
# define ERR_CMB "Error! Combination is unknown"
# define ERR_SYN "Error! Syntax"
# define ERR_CHR "Error! Syntax. Character (or combination) not handled"
# define ERR_SPL "Error! Simple quote is missing"
# define ERR_DBL "Error! Double quote is missing"
# define ERR_FILEHDOC "Error! Opening file for heredoc"
# define ERR_FILEIN "Error! Cannot access the in-file"
# define ERR_FILEOUT "Error! Cannot access the out-file"
# define ERR_FILECPY "Error! Opening file for copy"

typedef struct s_lex			t_lex;
typedef struct s_pars			t_pars;
typedef struct s_shell			t_shell;
typedef struct s_token			t_token;
typedef struct s_command		t_command;
typedef struct s_lex_proc		t_lex_proc;
typedef struct s_pars_proc		t_pars_proc;
typedef struct s_exp_proc		t_exp_proc;
typedef struct s_redir_proc		t_redir_proc;
typedef struct s_hdoc			t_hdoc;
typedef struct s_hdoc_tab		t_hdoc_tab;
typedef struct s_cmd			t_cmd;
typedef enum e_char_ascii		t_char_ascii;
typedef enum e_char_types		t_char_types;
typedef enum e_lex_read_modes	t_lex_read_modes;
typedef enum e_pars_read_modes	t_pars_read_modes;
typedef enum e_exp_read_modes	t_exp_read_modes;
typedef enum e_redir_read_modes	t_redir_read_modes;
typedef enum e_lex_actions		t_lex_actions;
typedef enum e_pars_actions		t_pars_actions;
typedef enum e_exp_actions		t_exp_actions;
typedef enum e_redir_actions	t_redir_actions;
typedef enum e_token_types		t_token_types;
typedef enum e_err_codes		t_err_codes;
typedef int						(*t_lex_func)(t_lex *);
typedef int						(*t_pars_func)(t_pars *);
typedef int						(*t_exp_func)(t_pars *);
typedef int						(*t_redir_func)(t_pars *);
typedef struct s_envp_cpy		t_envp_cpy;

extern int						g_exit_code;

struct s_shell
{
	t_hdoc_tab	*hdoc_tab;
	t_cmd		*cmd;
	t_cmd		*cmd_head;
	t_envp_cpy	*envpc;
	t_envp_cpy	*envpc_head;
	int			pipefd[2];
	int			tmp_fd;
	int			exit_status;
	int			hdv;
	char		*retprompt;
	char		*cwd;
	char		**ms_env;
	char		**env_paths;
	t_lex		*lex;
	t_pars		*pars;
};

enum e_err_codes
{
	ERR_CD_CMB,
	ERR_CD_SYN,
	ERR_CD_CHR,
	ERR_CD_SPL,
	ERR_CD_DBL,
	LEN_ERR_CODES
};

enum e_token_types
{
	TOK_NEW,
	TOK_WORD,
	TOK_NEW_LINE,
	TOK_LSS,
	TOK_GRT,
	TOK_GGRT,
	TOK_HDOC,
	TOK_PIPE,
	TOK_AMP,
	TOK_OP_OR,
	TOK_OP_AND,
	TOK_ERR_MARK,
	TOK_ERR_SPL,
	TOK_ERR_DBL,
	TOK_END_OF_INPUT,
	LEN_TOKEN_TYPES
};

enum e_char_types
{
	ERR_CHAR,
	SEP_CHAR,
	STD_CHAR,
	SPL_CHAR,
	DBL_CHAR,
	ESCP_CHAR,
	PIPE_CHAR,
	AMP_CHAR,
	LT_CHAR,
	GT_CHAR,
	DOL_CHAR,
	END_CHAR,
	LEN_CHAR_TYPES
};

enum e_lex_actions
{
	LEX_ERR,
	LEX_NONE,
	LEX_CATCH,
	LEX_KEEP,
	LEX_DROP,
	LEX_TAKE,
	LEX_SKIP,
	LEX_REC,
	LEX_END,
	LEN_LEX_ACTIONS
};

enum e_pars_actions
{
	PARS_ERR,
	PARS_NONE,
	PARS_NEW,
	PARS_CATCH,
	PARS_KEEP,
	PARS_DROP,
	PARS_TAKE,
	PARS_SKIP,
	PARS_END,
	LEN_PARS_ACTIONS
};

enum e_exp_actions
{
	EXP_ERR,
	EXP_NONE,
	EXP_NEW,
	EXP_CATCH,
	EXP_KEEP,
	EXP_REC,
	EXP_DROP,
	EXP_TAKE,
	EXP_SKIP,
	EXP_END,
	EXP_DOL,
	EXP_ERR_DBL,
	EXP_ANALYSIS,
	LEN_EXP_ACTIONS
};

enum e_redir_actions
{
	REDIR_ERR,
	REDIR_NONE,
	REDIR_NEW,
	REDIR_CATCH,
	REDIR_KEEP,
	REDIR_DROP,
	REDIR_TAKE,
	REDIR_SKIP,
	REDIR_IN,
	REDIR_HDOC,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_DEL_TWO,
	REDIR_END,
	LEN_REDIR_ACTIONS
};

enum e_lex_read_modes
{
	CMB_ERR_LEX_RD_MD,
	SYN_ERR_LEX_RD_MD,
	CHR_ERR_LEX_RD_MD,
	SPL_ERR_LEX_RD_MD,
	DBL_ERR_LEX_RD_MD,
	NEW_LEX_RD_MD,
	STD_LEX_RD_MD,
	SPL_LEX_RD_MD,
	DBL_LEX_RD_MD,
	ESCP_LEX_RD_MD,
	PIPE_LEX_RD_MD,
	AMP_LEX_RD_MD,
	LT_LEX_RD_MD,
	GT_LEX_RD_MD,
	OR_LEX_RD_MD,
	AND_LEX_RD_MD,
	HDOC_LEX_RD_MD,
	GGRT_LEX_RD_MD,
	LEN_LEX_RD_MDS
};

enum e_pars_read_modes
{
	CMB_ERR_PARS_RD_MD,
	SYN_ERR_PARS_RD_MD,
	NEW_PARS_RD_MD,
	STD_PARS_RD_MD,
	SPL_PARS_RD_MD,
	DBL_PARS_RD_MD,
	ESCP_PARS_RD_MD,
	PIPE_PARS_RD_MD,
	AMP_PARS_RD_MD,
	LT_PARS_RD_MD,
	GT_PARS_RD_MD,
	OR_PARS_RD_MD,
	AND_PARS_RD_MD,
	HDOC_PARS_RD_MD,
	GGRT_PARS_RD_MD,
	LEN_PARS_RD_MDS
};

enum e_exp_read_modes
{
	CMB_ERR_EXP_RD_MD,
	NEW_EXP_RD_MD,
	STD_EXP_RD_MD,
	SPL_EXP_RD_MD,
	DBL_EXP_RD_MD,
	ESCP_EXP_RD_MD,
	PIPE_EXP_RD_MD,
	AMP_EXP_RD_MD,
	LT_EXP_RD_MD,
	GT_EXP_RD_MD,
	OR_EXP_RD_MD,
	AND_EXP_RD_MD,
	HDOC_EXP_RD_MD,
	GGRT_EXP_RD_MD,
	DOL_EXP_RD_MD,
	LEN_EXP_RD_MDS
};

enum e_redir_read_modes
{
	ERR_REDIR_RD_MD,
	NEW_REDIR_RD_MD,
	STD_REDIR_RD_MD,
	SPL_REDIR_RD_MD,
	DBL_REDIR_RD_MD,
	ESCP_REDIR_RD_MD,
	PIPE_REDIR_RD_MD,
	AMP_REDIR_RD_MD,
	LT_REDIR_RD_MD,
	GT_REDIR_RD_MD,
	OR_REDIR_RD_MD,
	AND_REDIR_RD_MD,
	HDOC_REDIR_RD_MD,
	GGRT_REDIR_RD_MD,
	LEN_REDIR_RD_MDS
};

enum e_char_ascii
{
	NUL = 0,
	HTAB = 9,
	NL = 10,
	VTAB = 11,
	FFEED = 12,
	CRET = 13,
	SP = 32,
	EXCL = 33,
	QUOT = 34,
	POUND = 35,
	DOLLAR = 36,
	PERCNT = 37,
	COMAND = 38,
	APOS = 39,
	LPAR = 40,
	RPAR = 41,
	AST = 42,
	PLUS = 43,
	COMMA = 44,
	MINUS = 45,
	PERIOD = 46,
	SOL = 47,
	DIGIT_0 = 48,
	DIGIT_1 = 49,
	DIGIT_2 = 50,
	DIGIT_3 = 51,
	DIGIT_4 = 52,
	DIGIT_5 = 53,
	DIGIT_6 = 54,
	DIGIT_7 = 55,
	DIGIT_8 = 56,
	DIGIT_9 = 57,
	COLON = 58,
	SEMI = 59,
	LT = 60,
	EQUALS = 61,
	GT = 62,
	QUEST = 63,
	COMMAT = 64,
	CAPITAL_A = 65,
	CAPITAL_B = 66,
	CAPITAL_C = 67,
	CAPITAL_D = 68,
	CAPITAL_E = 69,
	CAPITAL_F = 70,
	CAPITAL_G = 71,
	CAPITAL_H = 72,
	CAPITAL_I = 73,
	CAPITAL_J = 74,
	CAPITAL_K = 75,
	CAPITAL_L = 76,
	CAPITAL_M = 77,
	CAPITAL_N = 78,
	CAPITAL_O = 79,
	CAPITAL_P = 80,
	CAPITAL_Q = 81,
	CAPITAL_R = 82,
	CAPITAL_S = 83,
	CAPITAL_T = 84,
	CAPITAL_U = 85,
	CAPITAL_V = 86,
	CAPITAL_W = 87,
	CAPITAL_X = 88,
	CAPITAL_Y = 89,
	CAPITAL_Z = 90,
	LSBQ = 91,
	ESCP = 92,
	RSQB = 93,
	CIRC = 94,
	LOWBAR = 95,
	GRAVE = 96,
	SMALL_A = 97,
	SMALL_B = 98,
	SMALL_C = 99,
	SMALL_D = 100,
	SMALL_E = 101,
	SMALL_F = 102,
	SMALL_G = 103,
	SMALL_H = 104,
	SMALL_I = 105,
	SMALL_J = 106,
	SMALL_K = 107,
	SMALL_L = 108,
	SMALL_M = 109,
	SMALL_N = 110,
	SMALL_O = 111,
	SMALL_P = 112,
	SMALL_Q = 113,
	SMALL_R = 114,
	SMALL_S = 115,
	SMALL_T = 116,
	SMALL_U = 117,
	SMALL_V = 118,
	SMALL_W = 119,
	SMALL_X = 120,
	SMALL_Y = 121,
	SMALL_Z = 122,
	LCUB = 123,
	VERBAR = 124,
	RCUB = 125,
	TILDE = 126,
	DELETE = 127,
};

struct s_lex_proc
{
	t_lex_actions		buffer_action;
	t_lex_actions		char_action;
	t_lex_read_modes	lex_read_mode;
	t_token_types		token_type;
};

struct s_pars_proc
{
	t_pars_actions		token_action;
	t_pars_actions		pars_list_action;
	t_pars_read_modes	pars_read_mode;
};

struct s_exp_proc
{
	t_exp_actions		buffer_action;
	t_exp_actions		char_action;
	t_exp_read_modes	exp_read_mode;
	t_token_types		token_type;
};

struct s_redir_proc
{
	t_redir_actions		token_action;
	t_redir_actions		redir_list_action;
	t_redir_read_modes	redir_read_mode;
};

struct s_lex
{
	char		*temp;
	int			nb_taken_char;
	char		*user_input;
	char		*user_input_raw;
	char		forbidden[NB_FORBIDDEN];
	t_lex_proc	prev_decision;
	t_lex_proc	new_decision;
	t_lex_proc	decision[LEN_LEX_RD_MDS][LEN_CHAR_TYPES];
	char		*token_types[LEN_TOKEN_TYPES];
	t_lex_func	ft[LEN_LEX_ACTIONS];
	int			nb_of_tokens;
	int			nb_tcmd;
	t_token		*token;
};

struct s_pars
{
	t_cmd			*cmd;
	t_cmd			*cmd_head;
	char			*temp;
	int				expju;
	int				nb_taken_char;
	int				offset_start;
	int				start_std;
	int				start_dol;
	int				before_dol_mode;
	char			**ms_env;
	int				hdoc_i;
	t_hdoc			*hdoc_list;
	t_hdoc_tab		*hdoc_tab;
	char			*parser_text;
	int				exp_on;
	t_pars_proc		prev_pars_decision;
	t_pars_proc		new_pars_decision;
	t_pars_proc		pars_decision[LEN_PARS_RD_MDS][LEN_TOKEN_TYPES];
	t_exp_proc		prev_exp_decision;
	t_exp_proc		new_exp_decision;
	t_exp_proc		exp_decision[LEN_EXP_RD_MDS][LEN_CHAR_TYPES];
	t_redir_proc	prev_redir_decision;
	t_redir_proc	new_redir_decision;
	t_redir_proc	redir_decision[LEN_REDIR_RD_MDS][LEN_TOKEN_TYPES];
	char			*token_types[LEN_TOKEN_TYPES];
	t_pars_func		ft_pars[LEN_PARS_ACTIONS];
	t_exp_func		ft_exp[LEN_EXP_ACTIONS];
	t_redir_func	ft_redir[LEN_REDIR_ACTIONS];
	t_command		*command;
	int				nb_of_commands;
	int				nb_of_tokens;
	int				cmdsts;
	t_token			*token;
	t_token_types	crt_tok_type;
	int				fd_in;
	int				fd_out;
	char			*current_filename;
	char			*new_filename;
	int				current_fd;
	int				new_fd;
	int				dq_opened;
	int				sq_opened;
	int				ret;
	int				redir;
	int				initial_mode;
	int				i;
	int				j;
	int				k;
	int				count;
	int				r;
	int				last_infile_mode;
	int				mode0_fd_in;
	int				mode1_fd_in;
	int				there_hdoc;
	int				lock_there_hdoc;
	char			*str_gnl;
	int				ret_45;
	int				pid;
	int				status;
};

struct s_cmd
{
	int				id;
	int				nb_of_tokens;
	char			*cmd;
	char			**token;
	int				fd_in;
	int				fd_out;
	t_cmd			*prev;
	t_cmd			*next;
};

struct s_token
{
	char			*id;
	t_token_types	type;
	t_token			*prev;
	t_token			*next;
};

struct s_command
{
	int				id;
	int				nb_of_tokens;
	t_token			*token;
	t_command		*prev;
	t_command		*next;
	int				fd_in;
	int				fd_out;
};

struct s_hdoc
{
	char			*file_name;
	int				fd;
	t_hdoc			*prev;
	t_hdoc			*next;
};

struct s_hdoc_tab
{
	char			*file_name;
	int				fd;
};

/* ************************************************************************** */
/*                                 common_core.c                              */
/* ************************************************************************** */
int				ft_read_prompt(t_shell *shell);
int				ft_error_ctrl_c(t_shell *shell, t_pars *pars, t_lex *lex);
int				ft_there_hdoc(t_pars *pars, char *str);
int				ft_init_core(t_lex *lex, t_pars *pars, t_shell *shell);
int				ft_all_parsing_steps(t_lex *lex, t_pars *pars, t_shell *shell);
int				ft_error_return(t_lex *lex, t_pars *pars, t_shell *shell);
int				ft_around_lexer(t_lex *lex);
int				ft_around_parser(t_lex *lex, t_pars *pars);
int				ft_around_redirector(t_lex *lex, t_pars *pars);
int				ft_lexer(t_lex *lex);
int				ft_parser(t_lex *lex, t_pars *pars);
int				ft_expander(t_pars *pars);
int				ft_inner_loop_expander(t_pars *pars);
int				ft_redirector(t_pars *pars);
int				ft_finilize_fd_in(t_pars *pars);
int				ft_transformer(t_pars *pars);
void			ft_lstclear(t_cmd **lst, void (*del)(void *));
void			ft_lstclear2(t_token *lst, void (*del)(void *));
void			del2(void *data);
void			del(void *data);

/* ************************************************************************** */
/*                             common_initializations.c                       */
/* ************************************************************************** */
int				ft_init_lex_decisions(t_lex *lex);
int				ft_init_pars_decisions(t_pars *pars);
int				ft_init_exp_decisions(t_pars *pars);
int				ft_init_redir_decisions(t_pars *pars);
int				ft_init_first_lex_decisions(t_lex *lex);
int				ft_init_first_pars_decisions(t_pars *pars);
int				ft_general_initialize(t_lex *lex, t_pars *pars);
int				ft_init_expander(t_pars *pars);
int				ft_init_pars_counts(t_pars *pars);

/* ************************************************************************** */
/*                               common_debug.c                               */
/* ************************************************************************** */
void			ft_flag(void);
int				ft_debug_lex(t_lex *lex);
int				ft_debug_pars(t_pars *pars);
int				ft_debug_exp(t_pars *pars);
int				ft_debug_redir(t_pars *pars);
int				ft_debug_cmd_content(t_pars *pars);
int				ft_debug_content(t_lex *lex, t_pars *pars, char *choice);
int				ft_debug_lexer_content(t_lex *lex);
int				ft_debug_parser_content(t_pars *pars);
int				ft_debug_expander_content(t_pars *pars);
int				ft_debug_redirector_content(t_pars *pars);
int				ft_debug_transformer_content(t_cmd *cmd);
void			reset_hd(t_shell *shell);

/* ************************************************************************** */
/*                            redirector_heredoc.c                            */
/* ************************************************************************** */
int				ft_open_heredoc(t_pars *pars, char *delim);
int				ft_hdoc_ctrl_c(t_pars *pars, char *file_name);
int				ft_check_delim(t_pars *pars, char *delim);
t_hdoc			*ft_new_hdoc(char *str, int fd);
t_hdoc			*ft_hdoc_addnext(t_hdoc *current, t_hdoc *next);
t_hdoc			*ft_hdoc_jumpcurrent(t_hdoc *prev, t_hdoc *next);
t_hdoc			*ft_hdoc_list_freeone(t_hdoc *hdoc);
int				ft_free_hdoclist(t_hdoc *hdoc);
int				ft_count_list(t_hdoc *hdoc_list);
t_hdoc_tab		*ft_hdoc_list_to_tab(t_hdoc *hdoc_list, int count);
int				ft_free_hdoctab(t_hdoc_tab *hdoc_tab);
int				ft_unlink_allhdoc(t_hdoc_tab *hdoc_tab);
int				ft_is_hdoc(char *file_name, t_pars *pars);
char			*ft_generate_valid_hdoc_name(t_pars *pars);
int				ft_change_hdoc_filename(t_pars *pars);
int				ft_copy_hdoc_new_name(t_pars *pars);
int				ft_update_hdoc_list(t_pars *pars);
int				ft_update_command_fds(t_pars *pars);
int				ft_debug_hdoc_list(t_hdoc *hdoc);
t_shell			*free_heredoc(t_shell *shell, int mode);
int				ft_free_commandtoken(t_pars *pars);
void			ft_pas_d_env(char *cwd, char *tmp2, t_envp_cpy **lst);
int				ft_little_add(int c, int p, t_envp_cpy **lst, char *tmp2);

/* ************************************************************************** */
/*                           redirector_file_manager.c                        */
/* ************************************************************************** */
int				ft_open_infile(t_pars *pars, char *file);
int				ft_open_outfile(t_pars *pars, char *file);
int				ft_open_append_outfile(t_pars *pars, char *file);

/* ************************************************************************** */
/*                              common_labels.c                               */
/* ************************************************************************** */
char			*ft_getlabel_error_msgs(const t_err_codes index);
char			*ft_getlabel_error_msgs_txt(const t_err_codes index);
char			*ft_getlabel_token_types(const t_token_types index);
char			*ft_getlabel_char_types(const t_char_types index);
char			*ft_getlabel_lex_actions(const t_lex_actions index);
char			*ft_getlabel_pars_actions(const t_pars_actions index);
char			*ft_getlabel_exp_actions(const t_exp_actions index);
char			*ft_getlabel_redir_actions(const t_redir_actions index);
char			*ft_getlabel_lex_read_modes(const t_lex_read_modes index);
char			*ft_getlabel_pars_read_modes(const t_pars_read_modes index);
char			*ft_getlabel_exp_read_modes(const t_exp_read_modes index);
char			*ft_getlabel_redir_read_modes(const t_redir_read_modes index);

/* ************************************************************************** */
/*                           common_memory.c                                  */
/* ************************************************************************** */
void			ft_bzero(void *s, size_t n);
int				ft_mallocator(void *ptr, size_t size);
int				ft_tklist_freeall(t_lex *lex);
int				ft_execfree_freeall(t_pars *pars);
int				ft_pars_freeall(t_pars *pars);
void			ft_lstclear(t_cmd **lst, void (*del)(void *));
void			ft_lstdelone(t_cmd *lst, void (*del)(void *));
void			del(void *data);

/* ************************************************************************** */
/*                            common_error.c                                  */
/* ************************************************************************** */
int				ft_msgerr(char	*str);

/* ************************************************************************** */
/*                            lexer_list.c                                    */
/* ************************************************************************** */
t_token			*ft_new_token(char *str);
t_token			*ft_token_addnext(t_token *current, t_token *next);
t_token			*ft_token_jumpcurrent(t_token *prev, t_token *next);
int				ft_free_tokenlist(t_token **token);
t_token			*ft_free_one_token(t_token *token);

/* ************************************************************************** */
/*                           parser_list.c                                    */
/* ************************************************************************** */
t_command		*ft_new_command(t_token *token);
t_command		*ft_command_addnext(t_command *current, t_command *next);
t_command		*ft_command_jumpcurrent(t_command *prev, t_command *next);
int				ft_free_commandlist(t_command *command);

/* ************************************************************************** */
/*                         lexer_init_decisions.c                             */
/* ************************************************************************** */
int				ft_init_lex_decision_1(t_lex *lex);
int				ft_init_lex_decision_2(t_lex *lex);
int				ft_init_lex_decision_3(t_lex *lex);
int				ft_init_lex_decision_4(t_lex *lex);
int				ft_init_lex_decision_5(t_lex *lex);
int				ft_init_lex_decision_6(t_lex *lex);
int				ft_init_lex_decision_7(t_lex *lex);
int				ft_init_lex_decision_8(t_lex *lex);
int				ft_init_lex_decision_9(t_lex *lex);

/* ************************************************************************** */
/*                        parser_init_decisions.c                             */
/* ************************************************************************** */
int				ft_init_pars_decision_1(t_pars *pars);
int				ft_init_pars_decision_2(t_pars *pars);
int				ft_init_pars_decision_3(t_pars *pars);
int				ft_init_pars_decision_4(t_pars *pars);
int				ft_init_pars_decision_5(t_pars *pars);
int				ft_init_pars_decision_6(t_pars *pars);
int				ft_init_pars_decision_7(t_pars *pars);

/* ************************************************************************** */
/*                       expander_init_decisions.c                            */
/* ************************************************************************** */
int				ft_init_exp_decision_1(t_pars *pars);
int				ft_init_exp_decision_2(t_pars *pars);
int				ft_init_exp_decision_3(t_pars *pars);
int				ft_init_exp_decision_4(t_pars *pars);
int				ft_init_exp_decision_5(t_pars *pars);
int				ft_init_exp_decision_6(t_pars *pars);
int				ft_init_exp_decision_7(t_pars *pars);
int				ft_init_exp_decision_8(t_pars *pars);
int				ft_init_exp_decision_9(t_pars *pars);

/* ************************************************************************** */
/*                     redirector_init_decisions.c                            */
/* ************************************************************************** */
int				ft_init_redir_decision_1(t_pars *pars);
int				ft_init_redir_decision_2(t_pars *pars);
int				ft_init_redir_decision_3(t_pars *pars);

/* ************************************************************************** */
/*                         lexer_apply_decision.c                             */
/* ************************************************************************** */
int				ft_lex_apply_decision(t_lex *lex);

/* ************************************************************************** */
/*                         parser_apply_decision.c                            */
/* ************************************************************************** */
int				ft_pars_apply_decision(t_pars *pars);

/* ************************************************************************** */
/*                        expander_apply_decision.c                           */
/* ************************************************************************** */
int				ft_exp_apply_decision(t_pars *pars);
int				ft_initial_mode_1(t_pars *pars, t_char_types *arg2);
int				ft_initial_mode_2(t_pars *pars, t_char_types *arg2);

/* ************************************************************************** */
/*                       redirector_apply_decision.c                          */
/* ************************************************************************** */
int				ft_redir_apply_decision(t_pars *pars);

/* ************************************************************************** */
/*                            lexer_actions.c                                 */
/* ************************************************************************** */
int				ft_check_forbidden_cmb(char *user_input);
int				ft_init_lex_actions(t_lex *lex);
int				ft_lex_none(t_lex *lex);
int				ft_lex_catch(t_lex *lex);
int				ft_lex_keep(t_lex *lex);
int				ft_lex_drop(t_lex *lex);
int				ft_lex_take(t_lex *lex);
int				ft_lex_skip(t_lex *lex);
int				ft_lex_record(t_lex *lex);
int				ft_lex_end(t_lex *lex);
int				ft_lex_err(t_lex *lex);

/* ************************************************************************** */
/*                            parser_actions.c                                */
/* ************************************************************************** */
int				ft_init_pars_actions(t_pars *pars);
int				ft_pars_none(t_pars *pars);
int				ft_pars_new(t_pars *pars);
int				ft_pars_catch(t_pars *pars);
int				ft_pars_keep(t_pars *pars);
int				ft_pars_drop(t_pars *pars);
int				ft_pars_take(t_pars *pars);
int				ft_pars_skip(t_pars *pars);
int				ft_pars_record(t_pars *pars);
int				ft_pars_end(t_pars *pars);
int				ft_pars_err(t_pars *pars);

/* ************************************************************************** */
/*                           expander_actions.c                               */
/* ************************************************************************** */
char			*ft_initial_expansion(t_lex *lex, t_pars *pars);
int				ft_init_exp_actions(t_pars *pars);
int				ft_exp_none(t_pars *pars);
int				ft_exp_analysis(t_pars *pars);
int				ft_exp_new(t_pars *pars);
int				ft_exp_catch(t_pars *pars);
int				ft_exp_keep(t_pars *pars);
int				ft_exp_drop(t_pars *pars);
int				ft_exp_take(t_pars *pars);
int				ft_exp_skip(t_pars *pars);
int				ft_exp_record(t_pars *pars);
char			*ft_init_exp_temp(t_pars *pars);
char			*ft_tempjoin(char **temp1, char **temp2);
char			*ft_getenv(char *temp2, t_pars *pars);
int				ft_exp_record_dol(t_pars *pars);
int				ft_exp_record_dol_part2(t_pars *pars, char *temp1);
int				ft_exp_record_dol_part3(t_pars *pars, char *temp1);
int				ft_exp_dol(t_pars *pars);
int				ft_exp_eq(t_pars *pars);
int				ft_exp_excd(t_pars *pars);
char			*ft_find_envstr(char *str, t_pars *pars);
int				ft_find_eq(char *env_str);
int				ft_exp_end(t_pars *pars);
int				ft_exp_err(t_pars *pars);

/* ************************************************************************** */
/*                          redirector_actions.c                              */
/* ************************************************************************** */
int				ft_init_redir_actions(t_pars *pars);
int				ft_inner_loop_heredoc(t_pars *pars, char *delim);
int				ft_redir_none(t_pars *pars);
//int				ft_redir_new(t_pars *pars);
int				ft_redir_catch(t_pars *pars);
int				ft_redir_keep(t_pars *pars);
int				ft_redir_drop(t_pars *pars);
//int				ft_redir_take(t_pars *pars);
int				ft_redir_skip(t_pars *pars);
int				ft_redir_record(t_pars *pars);
int				ft_redir_in(t_pars *pars);
int				ft_redir_heredoc(t_pars *pars);
int				ft_redir_out(t_pars *pars);
int				ft_redir_out_append(t_pars *pars);
int				ft_redir_del_two(t_pars *pars);
int				ft_redir_end(t_pars *pars);
int				ft_redir_err(t_pars *pars);

/* ************************************************************************** */
/*                             common_ascii.c                                 */
/* ************************************************************************** */
int				ft_char_type(char c);

/* ************************************************************************** */
/*                           transformer_list.c                               */
/* ************************************************************************** */
t_cmd			*ft_new_cmd(char **token);
t_cmd			*ft_cmd_addnext(t_cmd *current, t_cmd *next);
char			**ft_token_list_to_tab(t_command *command);
int				ft_free_cmdlist(t_cmd *cmd);
int				ft_free_tokentab(char **token, int len);

/* ************************************************************************** */
/*                               tests_main.c                                 */
/* ************************************************************************** */
//int				main(void);
int				ft_tests(void);

/* ************************************************************************** */
/*                                 EXEC PART                                  */
/* ************************************************************************** */
struct	s_envp_cpy
{
	char		*var;
	t_envp_cpy	*next;
};

void			ft_envpc_clear(t_envp_cpy **lst, void (*del)(void *));
void			ft_lstdel_envpc(t_envp_cpy *lst, void (*del)(void *));
int				ft_strcmp(char *s1, char *s2);
char			**ft_split(char const *s, char c);
int				export(t_shell *shell, char **av,
					t_envp_cpy **envpc_lst);
int				ft_exportcmp(char *s1, char *s2);
int				export_no_args(t_shell *shell, t_envp_cpy *envpc_lst);
int				export_error(char *str, int i, int error_type);
char			*ft_shlvl(char *var, char *tmp2);
int				ft_strccmp(char *s1, char *s2, char c);
int				is_env_var(char *str);
void			mod_env_var(char *var, t_envp_cpy *envpc_lst, int mode);
int				env_var_exists(char *str, char **envpc);
int				env_var_exists_export(char *str, t_envp_cpy *envpc);
int				is_valid_identifier(char c);
int				is_valid_string(char *str);
int				check_if_equal(char *str);
int				unset(int ac, char **av, t_envp_cpy **envpc_lst);
char			*ft_strjoin(char const *s1, char const *s2);
char			**dup_tab(char **tab);
void			free_tab(char **tab);
int				get_tab_size(char **tab);
int				cd(t_shell *shell, char **path, char **envp,
					t_envp_cpy **envpc_lst);
char			*get_home_path(char **envp);
int				pwd(int ac, char **av, int fd);
void			write_arg(char *str, int fd);
int				n_flag_present(char *str);
int				echo(int ac, char **av, int fd);
int				env(t_shell *shell, char **envp, int mode);
t_envp_cpy		*set_env(t_shell *shell, char **envp);
int				ft_exit(int ac, char **av, t_shell *shell, int fork);
int				get_formated_status(char *arg);
int				is_exit_arg_valid(char *arg);
int				invalid_exit_arg(char *arg);
long long		ft_atoll(const char	*str);
void			clean_exit(int status, t_shell *shell, char **av, int fork);
void			child_signals(void);
void			close_cmd_fds(t_cmd *cmd);
void			sigquit_cmd(int sig);
void			debug_display(t_shell *shell);
int				ft_wait(int *pid, t_shell *shell);
void			display_signal_intercept(int sig);
void			sigquit_ignore(int sig);
int				check_builtins(t_shell *shell);
int				exec_builtin(t_shell *shell, int fork);
void			sigint_handler(int sig);
void			sigint_heredoc(int sig);
int				start_shell(t_shell *shell);
int				is_valid_history(char *str);
int				command_not_found(t_shell *shell);
int				cmds_get_n(t_shell *shell);
int				start_exec(t_shell *shell, char **envp);
int				continue_exec(t_shell *shell, char **envp);
int				end_exec(t_shell *shell, char **envp);
int				pipeline(t_shell *shell, char **envp);
int				exit_pipeline(t_shell *shell, char **envp);
void			prep_pipexec(int *pids, int tbc);
int				pipexec(t_shell *shell, int tbc, char **envp, int *pids);
int				*make_pid_tab(int size);
int				set_fds(t_shell *shell);
int				exec(t_shell *shell, char **envp);
int				check_for_invalid_cmd(t_shell *shell);
int				simple_exec(t_shell *shell, char **envp);
int				prep_exec(t_shell *shell, char **envp);
void			free_cmd_lst(t_cmd *cmd);
void			free_cmd_link(t_cmd *cmd);
void			free_cmd_if(t_shell *shell);
void			free_all(t_shell *shell);
char			**build_minimal_env(void);
char			**lst_to_envp(t_envp_cpy *envpc_lst);
t_envp_cpy		*envp_to_lst(char **envp);
int				get_envp_lst_size(t_envp_cpy *envpc_lst);
void			clear_envpc_lst(t_envp_cpy *envpc_lst);
void			ft_env_varadd_back(t_envp_cpy **envpc_lst, t_envp_cpy *new);
t_envp_cpy		*ft_envpcnew(char *var);
char			*find_path(char *cmd, char **env_paths);
char			**get_env_paths(char **envp);
t_shell			*minishell_init(char **envp);
void			minishell_loop(t_shell *shell);
void			reset_shell_values(t_shell *shell);
int				ft_free_commandtokenlol(t_command *command);

#endif
