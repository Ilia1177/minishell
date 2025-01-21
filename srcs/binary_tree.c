/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/21 16:04:03 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bintree	*make_node(t_bintree *left, t_bintree *right, t_token *token)
{
	t_bintree	*root;

	root = malloc(sizeof(t_bintree));
	printf("make node %p with token %s\n", root, token->input);
	root->type = token->type;
	root->content = malloc(sizeof (char *) * 2);
	root->content[0] = ft_strdup(token->input);
	root->content[1] = NULL;
	root->left = left;
	root->right = right;
	return (root);
}

int	handle_parenthesis(t_token **current_token, t_type *type)
{
	t_token	*token;

	token = *current_token;
	while (token && !ft_strcmp(token->input, "("))
	{
		printf("type +1\n");
		*type += 1;
		token = token->next;
	}
	while (token && !ft_strcmp(token->input, ")"))
	{
		printf("type -1\n");
		*type -= 1;
		token = token->next;
	}
	*current_token = token;
	return (0);
}

t_bintree	*build_tree(t_token **head, t_type type)
{
	t_token		*current_token;
	t_bintree	*new_root;
	t_bintree	*old_root;

	current_token = *head;
	if (!current_token)
		return (NULL);
	printf("building new tree\n");
	while (current_token)
	{
		handle_parenthesis(&current_token, &type);
		printf("current token = %s, type = %d\n", current_token->input, type);
		//if (type != && type <= current_token->type)

		if (current_token->type == PIPE && type > 1)
			break ;	
		if ((current_token->type == OPERATOR && type > 0))
		{
			//printf("Break ! type = %d vs token type = %d\n", type, current_token->type);
			printf("break\n");
			break ;
		}
		if (current_token->type == CMD)
		{
			printf("token %s is CMD\n", current_token->input);
			new_root = make_node(NULL, NULL, current_token);
			old_root = new_root;
			current_token = current_token->next;
		}
		else
		{
			printf("token is not CMD\n");
			new_root = make_node(NULL, NULL, current_token);
			new_root->left = old_root;
			printf("%s->left = %s\n", new_root->content[0], old_root->content[0]);
			current_token = current_token->next;
			printf("attempt to buil tree on %s->right with token %s and type %d\n", new_root->content[0], current_token->input, current_token->type);
			new_root->right = build_tree(&current_token, 1 + type);
			printf("Done : %s->right = %s\n", new_root->content[0], new_root->right->content[0]);
			old_root = new_root;
		}
	}
	*head = current_token; // new
	printf("end of tree : root returned is = %s\n", new_root->content[0]);
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
