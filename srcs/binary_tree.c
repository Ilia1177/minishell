/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 11:44:23 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bintree	*make_node(t_bintree *left, t_bintree *right ,t_token *token)
{
	t_bintree *root;

	root = malloc(sizeof(t_bintree));
	printf("make token %p with %s\n", root, token->content[0]);
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
t_bintree	*build_tree(t_token **head, t_type type)
{
	t_token		*current_token;
	t_bintree	*new_root;
	t_bintree	*old_root;

	current_token = *head;
	if (!current_token)
		return (NULL);
	old_root = NULL;
	printf("Build tree from token %s\n", current_token->content[0]);
	while (current_token)
	{
		printf("current_token = ");
		print_args(current_token->content);
		printf("\n");
		if (type != CMD)
		{
			if (current_token->type == PIPE)
			{
				if (type == PIPE || type == OPERATOR)
				{
					printf("exit from the tree->>%s\n", new_root->content[0]);
					*head = current_token;
					break ;
				} 
			}
			if (current_token->type == OPERATOR)
			{
				if (type == OPERATOR)
				{
					printf("exit from the tree->>%s\n", new_root->content[0]);
					*head = current_token;
					break ;
				} 
			}

		}
		if (current_token->type == CMD)
		{
			new_root = make_node(NULL, NULL, current_token);
			old_root = new_root;
			current_token = current_token->next;
		}
		else if (current_token->type == OPERATOR)
		{

			new_root = make_node(NULL, NULL, current_token);
			new_root->left = old_root;
			printf("\"%s\"->left : %s\n",new_root->content[0], new_root->left->content[0]);
			current_token = current_token->next;
			printf("Attempt : \"%s\"->right :%s\n", new_root->content[0], current_token->content[0]);
			new_root->right = build_tree(&current_token, OPERATOR); // 2	
			printf("DONE : \"%s\"->right :%s\n", new_root->content[0], new_root->right->content[0]);
			if (!current_token->next)
				return (new_root);
			old_root = new_root;
		}
		else if (current_token->type == PIPE)
		{
			new_root = make_node(NULL, NULL, current_token);
			new_root->left = old_root;
			printf("\"%s\"->left : %s\n",new_root->content[0], new_root->left->content[0]);
			current_token = current_token->next;
			printf("Attempt : \"%s\"->right :%s\n", new_root->content[0], current_token->content[0]);
			new_root->right = build_tree(&current_token, PIPE); // 2	
			printf("DONE : \"%s\"->right :%s\n",new_root->content[0], new_root->right->content[0]);
			if (!current_token->next)
				return (new_root);
			old_root = new_root;
		}
//		else if (current_token->type == OUT_RDIR)
//		{
//			old_root->left = current_leaf;
//			current_token = current_token->next;
//		}
	}
	print_tree(new_root);
	printf("end_of_construction! Actual returned root is : %s\n", new_root->content[0]);
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
