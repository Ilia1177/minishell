/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/21 18:46:19 by ilia             ###   ########.fr       */
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

int	handle_parenthesis(t_token **current_token, int *priority)
{
	t_token	*token;

	token = *current_token;
	while (token && !ft_strcmp(token->input, "("))
	{
		printf("priority -1\n");
		*priority -= 1;
		token = token->next;
	}
	if (!ft_strcmp(token->input, ")"))
	{
		while (token && !ft_strcmp(token->input, ")"))
		{
			printf("priority +1\n");
			*priority += 1;
			token = token->next;
		}
		*current_token = token;
		printf("end of parenthesis\n");
		return (1);
	}
	*current_token = token;
	return (0);
}

t_bintree	*build_tree(t_token **head, int priority)
{
	t_token		*current_token;
	t_bintree	*new_root;
	t_bintree	*old_root;

	current_token = *head;
	if (!current_token)
		return (NULL);
	printf("building new tree with priority = %d\n", priority);
	while (current_token)
	{
		if (handle_parenthesis(&current_token, &priority) && priority < 0)
			break ;
		printf("current token = %s, priority = %d\n", current_token->input, priority);
		//if (priority != && priority <= current_token->priority)

		if (current_token->type == PIPE && priority > PIPE)
			break ;	
		else if (current_token->type == OPERATOR && priority > 0)
		{
			printf("Break ! priority = %d > 0, token_type = %d\n", priority, current_token->type);
			break ;
		}
		else if (current_token->type == CMD)
		{
			printf("token %s is CMD\n", current_token->input);
			new_root = make_node(NULL, NULL, current_token);
			old_root = new_root;
			current_token = current_token->next;
		}
		else
		{
			printf("token %s is NOT CMD\n", current_token->input);
			new_root = make_node(old_root, NULL, current_token);
			printf("%s->left = %s\n", new_root->content[0], old_root->content[0]);
			current_token = current_token->next;
			printf("attempt to build tree on %s->right with token %s and priority %d\n", new_root->content[0], current_token->input, 1 + priority);
			new_root->right = build_tree(&current_token, 1 + (int)new_root->type);
			printf("Done : %s->right = %s\n", new_root->content[0], new_root->right->content[0]);
			old_root = new_root;
		}
	}
	if (!current_token)
		printf("end of the command line\n");
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
