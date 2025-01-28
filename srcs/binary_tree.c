/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:29:00 by npolack           #+#    #+#             */
/*   Updated: 2025/01/28 20:44:46 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	redir_cpy(t_token *token, t_bintree *leaf) */
/* { */
/* 	if (token->cmd->) */
/* 	if (token->cmd->in_rdir) */
/* 		leaf->in_rdir = ft_strdup(token->cmd->in_rdir); */
/* 	else */
/* 		leaf->in_rdir = NULL; */
/* 	if (token->cmd->out_rdir) */
/* 		leaf->out_rdir = ft_strdup(token->cmd->out_rdir); */
/* 	else */
/* 		leaf->out_rdir = NULL; */
/* 	if (token->cmd->append) */
/* 		leaf->append = ft_strdup(token->cmd->append); */
/* 	else */
/* 		leaf->append = NULL; */
/* 	if (token->cmd->heredoc) */
/* 		leaf->heredoc = ft_strdup(token->cmd->heredoc); */
/* 	else */
/* 		leaf->heredoc = NULL; */
/* } */	

t_bintree	*make_node(t_bintree *left, t_bintree *right, t_token **token)
{
	t_bintree	*root;
	t_token		*current_token;

	current_token = *token;
	root = malloc(sizeof(t_bintree));
	root->type = current_token->type;
	root->input = ft_strdup(current_token->input);
	if (current_token->type == CMD)
		root->cmd = current_token->cmd;
		/* root->cmd = cmddup(current_token->cmd); */
	else 
		root->cmd = NULL;
	//redir_cpy(current_token, root);
	root->left = left;
	root->right = right;
	current_token = current_token->next;
	*token = current_token;
	return (root);
}

int	handle_parenthesis(t_token **token, t_bintree **root, t_bintree **old_root)
{
	t_token		*current_token;
	t_bintree	*new_root;

	current_token = *token;
	if (!current_token)
		return (-1);
	if (!ft_strcmp(current_token->input, "("))
	{
		current_token = current_token->next;
		new_root = build_tree(&current_token, 0);
		*root = new_root;
		*old_root = new_root;
		*token = current_token;
		return (1);
	}
	else if (!ft_strcmp(current_token->input, ")"))
	{
		current_token = current_token->next;
		*token = current_token;
		return (-1);
	}
	return (0);
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
			break ;
		else if (curr->type == PIPE && priority == PIPE)
			break ;
		else if (curr->type == OPERATOR && priority >= OPERATOR)
			break ;
		else if (curr->type == CMD)
			new_root = make_node(NULL, NULL, &curr);
		else
		{
			new_root = make_node(old_root, NULL, &curr);
			new_root->right = build_tree(&curr, (int)new_root->type);
		}
		old_root = new_root;
	}
	*head = curr;
	return (new_root);
}

/*
t_bintree	*build_tree(t_token **head, int priority)
{
	t_token		*current_token;
	t_bintree	*new_root;
	t_bintree	*old_root;

	current_token = *head;
	if (!current_token)
		return (NULL);
	printf("building new tree with %s and priority = %d\n",current_token->input, priority);
	while (current_token)
	{
		printf("current token = %s, priority = %d\n", current_token->input, priority);
		if (!ft_strcmp(current_token->input, "("))
		{
			current_token = current_token->next;
			new_root = build_tree(&current_token, 0);
			old_root = new_root;
			continue ;
		}
		else if (!ft_strcmp(current_token->input, ")"))
		{
			current_token = current_token->next;
			break ;
		}
		else if (current_token->type == PIPE && priority == PIPE)
		{
			printf("break on PIPE\n");
			break ;	
		}
		else if (current_token->type == OPERATOR && priority >= OPERATOR)
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
			new_root->right = build_tree(&current_token, (int)new_root->type);
			printf("Done : %s->right = %s\n", new_root->content[0], new_root->right->content[0]);
			old_root = new_root;
		}
	}
	*head = current_token; // new
	printf("end of tree : root returned is = %s\n", new_root->content[0]);
	return (new_root);
}*/
