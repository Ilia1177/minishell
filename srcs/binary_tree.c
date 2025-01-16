/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/16 19:20:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bintree *build_tree(t_list *start)
{
	t_bintree	*root;
	t_bintree	*old_root;
	t_token		*current_token;

	if (!start)
		return (-1);
	current_token = start;
	old_root = NULL;
	while (current_token)
	{
		root = malloc(sizeof(t_bintree));
		root->content = current_token;
		root->left = old_root;
		old_root = root;
		root->right = NULL;
		current_token = current_token->next;
	}
	return (root);
}

void	free_tree(t_bintree *root)
{
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	free(root->content);
}

void	print_tree(t_bintree *root)
{
	if (!root)
		return ;
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	printf("%s\n", root->content);
}
