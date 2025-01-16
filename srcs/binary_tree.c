/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/16 17:47:46 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bintree *build_tree(t_token *start)
{
	t_bintree	*root;
	t_bintree	*save_root;
	t_token		*current_token;

	if (!start)
		return (-1);
	current_token = start;
	while (current_token)
	{
		root = malloc(sizeof(t_bintree));
		root->content = dup_content(current_token);
		move_token = move_token->next;
		save_root = root;
	}	
	return (root);
}
