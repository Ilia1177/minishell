/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:18 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 16:23:37 by jhervoch         ###   ########.fr       */
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
	EXPAND,
	IN_RDIR,
	OUT_RDIR,
	OUT_ARDIR,
	HDOC,
	OUT_FILE,
	IN_FILE,
	VAR
}	t_type;

typedef enum e_mem_type
{
	LST,
	D_TAB,
	S_TAB,
	TREE
}	t_mem_type;


typedef struct s_token
{
	char			**content;
	t_type			type;
	char			*in;
	char			*out;
	int				error;
	struct s_token	*next;
}	t_token;

typedef struct s_bintree
{
	char				**content;
	t_type				type;
	struct s_bintree	*left;
	struct s_bintree	*right;
} t_bintree;


//binary_tree
t_bintree *build_tree(t_token *start);
void	free_tree(t_bintree *root);

//tokenize
//
t_token	*tokenize(char *prompt);
t_token *make_token(char *str, t_type type);
int	ft_nbword(const char *s);
char	**ft_split_token(char const *s);

// DEBUG
void	args_print(char **list);
void	print_tree(t_bintree *root);
#endif
