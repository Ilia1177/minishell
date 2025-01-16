/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/16 18:47:25 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bintree *build_tree(t_token *start)
{
	t_bintree	*root;
	t_bintree	*old_root;
	t_token		*current_token;

	if (!start)
		return (-1);
	current_token = start;
	while (current_token)
	{
		root = malloc(sizeof(t_bintree));
		root->content = current_token;
		root->left = old_root;
		old_root = root;
		root->left = NULL;
		root->right = NULL;
		current_token = current_token->next;
	}	
	return (root);
}
