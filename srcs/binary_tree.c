/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/17 18:03:29 by npolack          ###   ########.fr       */
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

//echo world > file && cat file | echo FAR >> file && cat file | grep FAR
t_bintree	*make_tree(t_token *head)
{
	t_bintree	*tree;

	while (head)
	{
		if (head->type == CMD)
			make_root(
		if (head->type == PIPE)
			make_root(make_tree(
	}
}

// build the binary tree from t_token *list (DO NOT FREE the t_token content)
t_bintree	*build_tree(t_token *head)
{
	t_bintree	*current_leaf;
	t_bintree	*new_root;
	t_bintree	*old_root;
	t_token		*current;

	if (!head)
		return (NULL);
	old_root = NULL;
	current = head;
	while (current)
	{
		current_leaf = make_root(NULL, NULL, current_token);
		if (current->type == CMD)
		{
			new_root = current_leaf;
			old_root = new_root;
		}
		if (current->type == OUT_RDIR)
		{
			old_root->left = current_leaf;
		}
		if (current->type == OPERATOR)
		{
			new_root = current_leaf;
			current_leaf->left = old_root;
			current_leaf->left = make_tree(current->next);
		}
		if (current->type == PIPE)
			return (old_root);
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
