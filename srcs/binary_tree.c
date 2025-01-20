/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 18:31:12 by npolack          ###   ########.fr       */
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

t_bintree	*build_tree(t_token **head, t_type type)
{
	t_token		*current_token;
	t_bintree	*new_root;
	t_bintree	*old_root;
	t_type		current_type;

	current_token = *head;
	if (!current_token)
		return (NULL);
	old_root = NULL;
	while (current_token)
	{
		if (!ft_strcmp(current_token->content[0], "("))
		{
			current_token = current_token->next;
			continue ;
		}
		if (!ft_strcmp(current_token->content[0], ")"))
		{
			current_token = current_token->next;
			*head = current_token;
			break ;
		}
		if (type != CMD)
		{
			if (current_token->type != CMD)
			{
				*head = current_token;
				break ;
			}
		}
		if (current_token->type == CMD)
		{
			new_root = make_node(NULL, NULL, current_token);
			old_root = new_root;
			current_token = current_token->next;
		}
		else
		{
			current_type = current_token->type;
			new_root = make_node(NULL, NULL, current_token);
			new_root->left = old_root;
			current_token = current_token->next;
			new_root->right = build_tree(&current_token, current_type);	
			if (!current_token->next)
				return (new_root);
			old_root = new_root;
		}
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
