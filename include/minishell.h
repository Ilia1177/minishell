/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:18 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 19:17:30 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>



typedef enum e_type
{
	CMD, 
	PIPE, 
	OPERATOR,
	EXPAND 
}	t_type;

typedef enum e_mem_type
{
	PTR,
	LST,
	D_TAB,
	S_TAB,
	TREE
}	t_mem_type;

typedef struct s_cmd
{
	char	**arg;
	int		error;
	char	*in;
	char	*out;
	int		pipe_in;
	int		pipe_out;
}	t_cmd;

typedef struct s_token
{
	//char			**content;
	char			*input;
	t_type			type;
	t_cmd			*cmd;
	//char			*in;
	//char			*out;
	//int				error;
	struct s_token	*next;
}	t_token;

typedef struct s_bintree
{
	int					stdfd[3]; // standar input(0)/output(1)/tmp_fd(2)
	int					pipefd[2]; // pipefd
	char				**content; // Malloc
	t_type				type;
	struct s_bintree	*left;
	struct s_bintree	*right;
} t_bintree;

typedef struct s_data
{
	char		**envp;
	char		*user_input;
	int			status;
	t_bintree	*tree;
	t_token		*list;
} t_data;

//binary_tree.c
t_bintree *build_tree(t_token **start, t_type priority);
void	free_tree(t_bintree *root);
void	free_leaf(t_bintree *leaf);

//tokenize.c
t_token	*tokenize(char *prompt);
t_token *make_token(char *str);
int	ft_nbword(const char *s);
char	**ft_split_token(char const *s);

//exec.c -> DOES NOT COMPILE (not included in makefile)
int	execute_tree(t_bintree *root, char **envp);

// DEBUG FUNCTION
void	print_list(t_token *list);
void	print_args(char **list);
void	print_tree(t_bintree *root);

//parsing.c

void	ft_lstiter_token(t_token *lst, void (*f)(t_token *));
void	type_token(t_token *token);

#endif
