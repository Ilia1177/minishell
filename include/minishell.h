/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:18 by npolack           #+#    #+#             */
/*   Updated: 2025/03/01 22:36:18 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>

# define IN 0
# define OUT 1
# define TMP 2
# define WARNING ": not a valid identifier"
# define SYNTERR "msh: syntax error. try again\n"
# define TM_ARG "msh: %s: too many arguments\n"
# define NR_ARG "msh: exit: %s: numeric argument required\n"
# define NMF_MSG "no matches found\n"
# define NOENT_MSG "msh: %s : No such file or directory\n"
# define ISDIR_MSG "msh: %s : Is a directory\n"
# define CMDNF_MSG "msh: %s : command not found\n"
# define PERMD_MSG "msh: %s : Permission denied\n"
# define FAR_MSG "msh: %s : filename argument required\n"

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

/*************************
 * @param stdfd[2] - in 0 - out 1 - tmp 2
**************************/
typedef struct s_bintree
{
	int					stdfd[2];
	int					pipefd[2];
	t_cmd				*cmd;
	char				*input;
	t_type				type;
	struct s_bintree	*left;
	struct s_bintree	*right;
}	t_bintree;

typedef struct s_data
{
	pid_t		pid;
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
extern int	g_signal_caught;

/****************************************/
/*         MINISHELL_RUNTIME            */
/****************************************/
//main.c
void		init_shell(t_data *data);
char		*listen_to_user(char *prompt);
int			run_shell(t_data *data);

//prompt.c
char		*listen_to_user(char *prompt);
char		*get_user_input(t_data *data);

//utils.c
int			ft_ischarset(char c, char *charset);
int			ft_isquote(char c);
int			is_space(char c);
int			is_all_space(char *str);
int			input_has_pipe(t_bintree *tree);

/***********SIGNAL***************/
//signals.c
int			register_sig_prompt(void);
void		handle_signals_prompt(int sig, siginfo_t *info, void *ctx);
void		handle_signals_exec(int sig, siginfo_t *info, void *ctx);
int			register_sig_exec(void);
//signals-utils.c
void		handle_signals_heredoc(int sig, siginfo_t *info, void *ctx);
int			register_sig_heredoc(void);

/***********FREE AND EXIT****************/
//cleanup.c
void		free_elem(void *elem, t_mem_type mem);
void		free_tabstr(char **tabstr);
void		free_minishell(t_data *data, int exit_code);

//cleanup_supp.c
void		free_cmd(t_cmd *cmd);
void		ft_free_bugsplit(char **str, int i);

// DEBUG FUNCTION
void		print_list(t_token *list, t_data *data);
void		print_args(char **list);
void		print_tree(t_bintree *root, int space, int start, t_data *data);

/****************************************/
/*            BINARY TREE               */
/****************************************/
//binary_tree.c
void		close_n_init_fd(int *fd);
void		init_fd(t_bintree *node);
t_bintree	*build_tree(t_token **start, int priority);
void		close_fd(t_bintree *node);
void		close_fd_tree(t_bintree *node);

#endif
