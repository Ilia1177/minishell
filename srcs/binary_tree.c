/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/18 10:49:20 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bintree	*make_node(t_bintree *left, t_bintree *right ,t_token *token)
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
/*
t_bintree	*make_little_tree(t_token *head, t_bintree *root)
{
	t_bintree	*current_leaf;
	t_bintree	*new_root;
	t_bintree	*old_root;
	t_token		*current_token;

	current_token = head;
	while (current_token)
	{
		current_leaf = make_node(NULL, NULL, current_token);
		if (current_token->type == CMD)
		{
			new_root = current_leaf;
			old_root = new_root;
		}
		else if (current_token->type == OPERATOR)
		{
			new_root = current_leaf;
			new_root->left = old_root;
			old_root = new_root;
			current_token = make_little_tree(current_token->next, new_root->right);
			current_token = current_token->next;

		}
		else if (current_token->type == PIPE)
		{
			current_leaf->left = old_root;
			current = make_little_tree(current_token->next, current_leaf);
		}
		else if (current_token


		token =  token->next;
	}
}
*/
//echo world > file && cat file | echo FAR >> file && cat file | grep FAR
// C || C | C | C && C || C
// build the binary tree from t_token *list (DO NOT FREE the t_token content)
t_bintree	*build_tree(t_token *current_token, t_type type)
{
	t_bintree	*new_root;
	t_bintree	*old_root;

	if (!current_token)
		return (NULL);
	old_root = NULL;
	printf("tree_construct :\n");
	while (current_token)
	{
		printf("Actual_token = ");
		print_args(current_token->content);
		printf("\n");
		if (current_token->type != CMD)
			if (current_token->type != type)
				break ;
		if (current_token->type == CMD)
		{
			new_root = make_node(NULL, NULL, current_token);;
			old_root = new_root;
			current_token = current_token->next;
		}
		else if (current_token->type == OPERATOR)
		{
			new_root = make_node(NULL, NULL, current_token);
			new_root->left = old_root;
			new_root->right = build_tree(current_token->next, OPERATOR); // 1
			old_root = new_root;
			current_token = current_token->next;
		}
		else if (current_token->type == PIPE)
		{
			new_root = make_node(NULL, NULL, current_token);
			new_root->left = old_root;
			new_root->right = build_tree(current_token->next, PIPE); // 2
			old_root = new_root;
			current_token = current_token->next;
		}
	//	else if (current_token->type == OUT_RDIR)
	//	{
	//		old_root->left = current_leaf;
	//		current_token = current_token->next;
	//	}
	}
	printf("end_of_construction\n");
	print_args(new_root->content);
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
