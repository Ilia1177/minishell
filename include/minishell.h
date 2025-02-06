/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:18 by npolack           #+#    #+#             */
/*   Updated: 2025/02/06 14:42:22 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define IN 0
# define OUT 1
# define TMP 2
# define WARNING ": not a valid identifier"
# define SYNTERR "minishell: syntax error near unexpected token"

typedef enum e_type
{
	CMD,
	OPERATOR,
	PIPE,
}	t_type;

typedef enum e_mem_type
{
	PTR,
	LST,
	D_TAB,
	TREE
}	t_mem_type;

typedef enum e_type_rdir
{
	R_IN,
	R_OUT,
	APPEND,
	HEREDOC
}	t_type_rdir;

typedef struct s_mem
{
	void			*elem;
	t_mem_type		type;
	struct s_mem	*next;
}	t_mem;

typedef struct s_rdir
{
	char		*name;
	t_type_rdir	type;	
}	t_rdir;

typedef struct s_cmd
{
	char	**args;
	t_rdir	*rdir;
	int		error;
}	t_cmd;

typedef struct s_token
{
	char			*input;
	t_type			type;
	t_cmd			*cmd;
	struct s_token	*next;
}	t_token;

typedef struct s_bintree
{
	int					stdfd[2]; // standar input(0)/output(1)/tmp_fd(2)
	int					pipefd[2]; // pipefd
	t_cmd				*cmd;
	char				*input;
	t_type				type;
	struct s_bintree	*left;
	struct s_bintree	*right;
}	t_bintree;

typedef struct s_data
{
	int			flag;
	char		*prompt;
	char		**paths;
	char		**envp;
	char		*user_input;
	int			status;
	t_bintree	*tree;
	t_token		*token_list;
	t_mem		*mem_list;
}	t_data;

//global variable
extern int	signal_caught;

/****************************************/
/*         MINISHELL RUNTIME            */
/****************************************/
//main.c
void		init_shell(t_data *data);
char		*listen_to_user(char *prompt);
int			run_shell(t_data *data);

/***********SIGNAL***************/
//signals.c
int			register_signals(void);
void		handle_signals(int sig, siginfo_t *info, void *ctx);
int			listen_to_signal(t_data *data);

/***********FREE AND EXIT****************/
//cleanup.c
void		free_elem(void *elem, t_mem_type mem);
void		free_tabstr(char **tabstr);
void		free_cmd(t_cmd *cmd);
void		free_minishell(t_data *data);
void		free_tree(t_bintree *root);
void		free_leaf(t_bintree *leaf);
void		close_all_fd(t_bintree *root);
void		ft_free_bugsplit(char **str, int i);

// DEBUG FUNCTION
void		print_list(t_token *list);
void		print_rdir(t_token *token);
void		print_args(char **list);
void		print_tree(t_bintree *root, int space);

/****************************************/
/*            BINARY TREE               */
/****************************************/
//binary_tree.c
t_bintree	*build_tree(t_token **start, int priority);

/****************************************/
/*             TOKENIZE                 */
/****************************************/
//tokenize.c
t_token		*build_tokenlist(char **tokens);
int			tokenize(t_data *data);

//redir.c
int			ft_nb_rdir(char *str);
int			true_wordlen(char *str);
int			catch_rdir(t_rdir	*rdir, char *str, t_type_rdir type, int num_rdir);
void		seek_rdir(char *str, t_rdir **s_rdir, t_data *data);

//make_elem.c
t_cmd		*make_cmd(void);
t_token		*make_token(char *str);
t_type		get_type(char *str);

//token_utils.c
int			ft_issep(char c);
int			ft_isquote(char c);
int			is_space(char c);
int			is_parenthesis(char c);

//token_tab.c
int			cmd_len(char *str);
int			sep_len(char *str);
int			ft_nbword(const char *s);
// void		ft_skip_quote(const char *s, int *index);
char		**ft_split_token(char const *s);

/*************LST_ITER_FUNC***********/
//lst_iter_func.c
void		unquote(t_token *token, t_data *data);
void		get_redir(t_token *token, t_data *data);
void		type_token(t_token *token, t_data *data);
void		split_args(t_token *token, t_data *data);
void		get_expand(t_token *token, t_data *data);

/****************************************/
/*                EXEC                  */
/****************************************/
//exec.c 
int			execute_tree(t_data *data);
int			connect_node(t_bintree *a, t_bintree *b);
int			execute_node(t_bintree *node, t_data *data);

//exec_utils.c
char		**get_paths(char **env);
char		*get_full_path(char **paths, char *str);
int			build_cmd(t_bintree *node, t_data *data);
char		**tab_dup(char **tab);
t_cmd		*cmddup(t_cmd *cmd);
int			update_envp(t_data *data, char *str);

/****************************************/
/*               PARSING                */
/****************************************/
//parsing.c
void		ft_lstiter_token(t_data *data, void (*f)(t_token *, t_data *));
int			ft_nb_args(const char *s);
int			arg_len(char *str);

//lst_utils.c
void		ft_lstdelone_token(t_token *lst, void (*del)(void*));
void		ft_lstclear_token(t_token **lst, void (*del)(void*));
void		ft_lst_split_dup(t_token **lst, int (*f)(), char *cmp);
int			ft_count_dup(char *s1, char *s2, char *dup);
void		iter_split_args(char *input, t_token **iter_token, int nb_args);

/*****************SYNTAX*****************/
//syntax.c
int			parenthesis_syntax(t_token *prev, t_token *curr);
int			catch_syntax_error(t_token *prev, t_token *curr);
int			syntax_error(char *str);

/***********QUOTE_UTILS****************/
//quote_utils.c
int		skip_quote(char *str, char quote);
char	find_next_quote(char *str);
char	*get_quotedword(char **str);
char	*get_cleanword(char **str);
char 	*remove_quote(char *str);

/****************************************/
/*               BUILTINS               */
/****************************************/
// Builtins
void		change_dir(t_bintree *node, t_data *data);
int			echo(t_bintree *node, t_data *data);
int			print_working_dir(t_bintree *node, t_data *data);
int			print_env(t_bintree *node, char **envp, char *format);
int			export(t_bintree *node, t_data *data);
void		unset(t_bintree *node, t_data *data);

/****************************************/
/*               HEREDOC                */
/****************************************/
//heredoc.c
char		*get_here_doc(char *lim, t_data *data);
char		*random_name(int nb_char);
int			catch_heredoc(t_rdir *rdir, char *str, t_data *data, int num_rdir);

/****************************************/
/*               EXPAND                 */
/****************************************/
//expand.c
int			expand_size(char *str, int pos);
int			insert_expand(char **input, int pos, char *exp);
int			find_expand(char *str);
char		*catch_expand(t_data *data, char *str);
void		expand_str(t_data *data, char **str);

/***********SYNTAX****************/
//syntax.c
int			parenthesis_syntax(t_token *prev, t_token *curr);
int			catch_syntax_error(t_token *prev, t_token *curr);
int			syntax_error(char *str);
int			open_parenthesis(char *str);
int			check_closing_quote(char *str);
#endif
