/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:18 by npolack           #+#    #+#             */
/*   Updated: 2025/01/27 20:55:56 by jhervoch         ###   ########.fr       */
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

typedef struct s_mem
{
	void			*elem;
	t_mem_type		type;
	struct s_mem	*next;
}	t_mem;

typedef struct s_cmd
{
	char	**args;
	int		error;
	char	*in;
	char	*out;
}	t_cmd;

typedef struct s_token
{
	char			*append;
	char			*in_rdir;
	char			*out_rdir;
	char			*heredoc;
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
	char				*append;
	char				*heredoc;
	char				*out_rdir;
	char				*in_rdir;
	t_type				type;
	struct s_bintree	*left;
	struct s_bintree	*right;
}	t_bintree;

typedef struct s_data
{
	char		*prompt;
	char		**paths;
	char		**envp;
	char		*user_input;
	int			status;
	t_bintree	*tree;
	//t_token		*list;
	t_token		*token_list;
	t_mem		*mem_list;
}	t_data;

//global variable
extern int	signal_caught;

//main.c
void		init_shell(t_data *data);
void		free_minishell(t_data *data);
char		*listen_to_user(char *prompt);
int			run_shell(t_data *data);

//binary_tree.c
t_bintree	*build_tree(t_token **start, int priority);
void		free_tree(t_bintree *root);
void		free_leaf(t_bintree *leaf);
void		close_all_fd(t_bintree *root);

//signals.c
int			register_signals(void);
void		handle_signals(int sig, siginfo_t *info, void *ctx);
int			listen_to_signal(t_data *data);

//tokenize.c
t_token		*tokenize(char *prompt);
t_token		*make_token(char *str, t_type type);
int			ft_nbword(const char *s);
char		**ft_split_token(char const *s);

void		get_redir(t_token *token);
int			true_wordlen(char *str);
int			catch_rdir(t_token *token, char *str);
int			catch_append(t_token *token, char *str);
int			catch_heredoc(t_token *token, char *str);
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

// DEBUG FUNCTION
void		print_list(t_token *list);
void		print_args(char **list);
void		print_tree(t_bintree *root, int space);

//parsing.c
void		ft_lstiter_token(t_token *lst, void (*f)(t_token *));
void		type_token(t_token *token);
void		split_args(t_token *token);
int			syntax_error(char *str);

//token_utils.c
int			ft_issep(char c);
int			ft_isquote(char c);
int			is_space(char c);
int			ft_len_until_quote(char *str);

//token_tab.c
void		ft_skip_quote(const char *s, int *index);
int			ft_nbword(const char *s);
void		ft_free_bugsplit(char **str, int i);

//lst_utils.c
void		ft_lstadd_front_mem(t_mem **lst, t_mem *new);
t_mem		*ft_lstnew_mem(void *elem, t_mem_type type);
void		ft_lstdelone_token(t_token *lst, void (*del)(void*));
void		ft_lstclear_token(t_token **lst, void (*del)(void*));
void		ft_lst_split_dup(t_token **lst, int (*f)(), char *cmp);
int			ft_count_dup(char *s1, char *s2, char *dup);

//cleanup.c
void		free_elem(void *elem, t_mem_type mem);
void		free_tabstr(char **tabstr);
void		free_cmd(t_cmd *cmd);

// Builtins
int			change_dir(t_data *data, char *path);

//heredoc.c
void	get_here_doc(char *lim);
char	*get_expand(char **env, char *str);
#endif
