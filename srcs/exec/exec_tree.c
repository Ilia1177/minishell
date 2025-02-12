/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:10:29 by npolack           #+#    #+#             */
/*   Updated: 2025/02/12 14:52:38 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_tree(t_data *data)
{
	int	exit_status;

	data->paths = get_paths(data->envp); 
	data->tree->stdfd[IN] = dup(0);
	data->tree->stdfd[OUT] = dup(1);
	exit_status = execute_node(data->tree, data);
	close(data->tree->stdfd[IN]);
	close(data->tree->stdfd[OUT]);
	return (exit_status);
}

int	make_pipe(t_bintree *node, t_data *data)
{
	int	exit_status;

	pipe(node->pipefd);	
	node->left->stdfd[OUT] = dup(node->pipefd[OUT]);
	node->left->stdfd[IN] = dup(node->stdfd[IN]);
	close(node->pipefd[OUT]);
	close(node->stdfd[IN]);
	exit_status = execute_node(node->left, data);
	if (node->right)
	{
		node->right->stdfd[OUT] = dup(node->stdfd[OUT]);
		node->right->stdfd[IN] = dup(node->pipefd[IN]);
		close(node->stdfd[OUT]);
		close(node->pipefd[IN]);
		exit_status = execute_node(node->right, data);
	}
	return (exit_status);
}

void	connect_stdio(t_bintree *a, t_bintree *b)
{
	b->stdfd[IN] = dup(a->stdfd[IN]);
	b->stdfd[OUT] = dup(a->stdfd[OUT]);
}

int	make_operation(t_bintree *node, t_data *data)
{
	int	exit_status;

	connect_stdio(node, node->left);
	exit_status = execute_node(node->left, data);
	if (!ft_strcmp(node->input, "||"))
	{
		if (exit_status && node->right)
		{
			connect_stdio(node, node->right);
			close(node->stdfd[IN]);
			close(node->stdfd[OUT]);
			exit_status = execute_node(node->right, data);
		}
		else
		{
			close(node->stdfd[IN]);
			close(node->stdfd[OUT]);
		}
		return (exit_status);
	}
	else if (node->right)
	{
		connect_stdio(node, node->right);
		exit_status = execute_node(node->right, data);
	}
	return (exit_status);
}

int	execute_node(t_bintree *node, t_data *data)
{
	int	exit_status;

	if (node->left)
	{
		if (node->type == PIPE)
			exit_status = make_pipe(node, data);
		else
			exit_status = make_operation(node, data);
		return (exit_status);
	}
	else
	{
		exit_status = exec_cmd(node, data);
	}
	return (exit_status);
}
