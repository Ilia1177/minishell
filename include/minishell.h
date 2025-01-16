/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:20:18 by npolack           #+#    #+#             */
/*   Updated: 2025/01/16 17:59:18 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_bintree
{
	char **content;
	enum type;
	t_bintree *left;
	t_bintree *right;
} t_bintree;


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

typedef struct s_token
{
	char **content;
	t_type	type;
	int		error;
	struct s_token *next;
}	t_token;


#endif
