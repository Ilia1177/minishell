/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:18 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 14:22:20 by npolack          ###   ########.fr       */
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
	PIPE, // |
	OPERATOR, // &&  || ()
	EXPAND, // EXPAND = VAR ?
	VAR // VAR = EXPAND ?
}	t_type;

typedef struct s_token
{
	char			**content;
	t_type			type;
	int				error;
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

//binary_tree.c
t_bintree *build_tree(t_token **start, t_type priority);
void	free_tree(t_bintree *root);
void	free_leaf(t_bintree *leaf);

//tokenize.c
t_token	*tokenize(char *prompt);
t_token *make_token(char *str, t_type type);

//exec.c -> DOES NOT COMPILE (not included in makefile)
int	execute_tree(t_bintree *root, char **envp);

// DEBUG FUNCTION
void	print_list(t_token *list);
void	print_args(char **list);
void	print_tree(t_bintree *root);
#endif
