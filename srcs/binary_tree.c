/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 16:17:37 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// build the binary tree from t_token *list (DO NOT FREE the t_token content)
t_bintree	*build_tree(t_token *start)
{
	t_bintree	*root;
	t_bintree	*old_root;
	t_token		*current_token;

	if (!start)
		return (NULL);
	current_token = start;
	old_root = NULL;
	while (current_token)/// current_token->next
	{
		root = malloc(sizeof(t_bintree));
		root->content = current_token->content;// do not free t_token content
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
	free(root->content[0]); // wrong
}

// print tree for DEBUG
void	print_tree(t_bintree *root)
{
	if (!root)
		return ;
	if (root->left)
		print_tree(root->left);
	if (root->right)
		print_tree(root->right);
	if (root->content)
	{
		args_print(root->content);
		printf("\n");
	}
}
