/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/02/19 17:49:22 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	init_fd(t_bintree *node)
{
	node->stdfd[IN] = -1;
	node->stdfd[OUT] = -1;
	node->pipefd[IN] = -1;
	node->pipefd[OUT] = -1;
}

void	close_fd(t_bintree *node)
{
	if (node->stdfd[IN] != -1 && node->stdfd[IN] != -2)
	{
		close(node->stdfd[IN]);
		node->stdfd[IN] = -1;
	}
	if (node->stdfd[OUT] != -1 && node->stdfd[OUT] != -2)
	{
		close(node->stdfd[OUT]);
		node->stdfd[OUT] = -1;
	}
	if (node->pipefd[IN] != -1 && node->pipefd[IN] != -2)
	{
		close(node->pipefd[IN]);
		node->pipefd[IN] = -1;
	}
	if (node->pipefd[OUT] != -1 && node->pipefd[OUT] != -2)
	{
		close(node->pipefd[OUT]);
		node->pipefd[OUT] = -1;
	}
}

void close_fd_tree(t_bintree *node)
{
	if (node->left)
		close_fd_tree(node->left);
	if (node->right)
		close_fd_tree(node->right);
	close_fd(node);
}

t_bintree	*make_node(t_bintree *left, t_bintree *right, t_token **token)
{
	t_bintree	*root;
	t_token		*current_token;
	t_token		*tmp;

	current_token = *token;
	root = malloc(sizeof(t_bintree));
	root->type = current_token->type;
	root->input = current_token->input;
	init_fd(root);
	if (current_token->type == CMD)
		root->cmd = current_token->cmd;
	else
		root->cmd = NULL;
	root->left = left;
	root->right = right;
	tmp = current_token;
	current_token = current_token->next;
	free(tmp);
	*token = current_token;
	return (root);
}

int	handle_parenthesis(t_token **token, t_bintree **root, t_bintree **old_root)
{
	t_token		*current_token;
	t_token		*tmp;

	current_token = *token;
	tmp = current_token;
	if (!current_token)
		return (-1);
	if (!ft_strcmp(current_token->input, "("))
	{
		current_token = current_token->next;
		*root = build_tree(&current_token, 0);
		*old_root = *root;
		*token = current_token;
		ft_lstdelone_token(tmp, &free);
		return (1);
	}
	else if (!ft_strcmp(current_token->input, ")"))
		return (-1);
	return (0);
}

t_bintree	*make_operator(t_token **curr, t_bintree *old_root)
{
	t_bintree	*new_root;

	new_root = make_node(old_root, NULL, curr);
	new_root->right = build_tree(curr, (int)new_root->type);
	return (new_root);
}

t_bintree	*build_tree(t_token **head, int priority)
{
	t_token		*curr;
	t_bintree	*new_root;
	t_bintree	*old_root;

	curr = *head;
	if (!curr)
		return (NULL);
	while (curr)
	{
		if (handle_parenthesis(&curr, &new_root, &old_root) == 1)
			continue ;
		else if (handle_parenthesis(&curr, &new_root, &old_root) == -1)
		{
			curr = curr->next;
			break ;
		}
		else if (curr->type == PIPE && priority == PIPE)
			break ;
		else if (curr->type == OPERATOR && priority >= OPERATOR)
			break ;
		else if (curr->type == CMD)
			new_root = make_node(NULL, NULL, &curr);
		else
			new_root = make_operator(&curr, old_root);
		old_root = new_root;
	}
	*head = curr;
	return (new_root);
}
