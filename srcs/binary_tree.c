/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/17 16:32:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bintree	*make_root(t_bintree *left, t_bintree *right ,t_token *token)
{
	t_bintree *root;

	root = malloc(sizeof(t_bintree));
	root->type = token->type;
	root->content = token->content;// do not free t_token content
	root->left = left;
	root->right = right;
	return (root);
}

// build the binary tree from t_token *list (DO NOT FREE the t_token content)
t_bintree	*build_tree(t_token *head)
{
	t_bintree	*new_leaf;
	t_bintree	*new_root;
	t_bintree	*old_root;
	t_token		*current_token;

	if (!head)
		return (NULL);
	old_root = NULL;
	current_token = head;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			new_leaf = make_root(NULL, NULL, current_token->next);
			new_root = make_root(old_root, new_leaf, current_token);
			old_root = new_root;
			current_token = current_token->next->next;
			continue ;
		}
		else if (current_token->type == OUT_RDIR)
			new_root = make_root(old_root, NULL, current_token);
		else if (current_token->type == CMD)
			new_root = make_root(NULL, NULL, current_token);
		old_root = new_root;
		current_token = current_token->next;
	}
	return (new_root);
}

void	free_leaf(t_bintree *leaf)
{
	int	i;

	i = -1;
	while (leaf->content[++i])
		free(leaf->content[i]);
	free(leaf->content[i]);
	free(leaf->content);
	free(leaf);
}

// free the all tree
void	free_tree(t_bintree *root)
{
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	free_leaf(root);
}
