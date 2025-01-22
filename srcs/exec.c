/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/01/22 03:33:24 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_bintree *node, t_data *data)
{
	int pid;
	int exit_status;

	// REDIR !!
	// if node->cmd->in
	pid = fork();
	if (!pid)
	{
		// access()
		execve(node->cmd->args[0], node->cmd->args, data->envp);
		//big_free()
	}
	else
	{
		waitpid(-1, &exit_status, NULL);
		data->status = WEXITSTATUS(exit_status);
	}
	return (exit_status);
}


int	make_operation(t_bintree *node, t_data *data)
{
	int	exit_status;

	else if (ft_strcmp(node->content[0], "||"))
	{
		if (!data->status)
			return (127);
		else
			return (0);
	}
	else if (ft_strcmp(node->content[0], "&&"))
		return (0);
}
int	execute_tree(t_data *data)
{
	dup2(tree->stdfd[0], 0);
	dup2(tree->stdfd[1], 1);
	execute_node(data->tree);
}
int	connect_node(t_bintree *a, t_bintree *b)
{
	dup2(a->stdfd[0], b->stdfd[0]);
	dup2(a->stdfd[1], b->stdfd[1]);
	return(0);
}
int	pipe_operation(t_bintree *a, t_bintree *b)
{
	pipe(a->stdfd[IN], b->pipefd[IN]);
	pipe(a->stdfd[OUT], b->pipefd[OUT]);
}
int	execute_node(t_bintree *node, t_data *data)
{
	int	exit_status;
	int	pid;


	if (node->left)
	{
		connect_node(node, node->left);
		if (node->type = PIPE)
			pipe_operation(node);
		exit_status = execute_node(node->left);
	}
	if (node->type = OPERATOR)
	{
		exit_status = make_operation(node, data);
		if (!exit_status && node->right)
		{
			connect_node(node, node->right);
			exit_status = execute_node(node->right);
		}

	}
	else if (node->type = CMD)
		exit_status = exec_cmd(node, data);

	if (!exit_status && node->right)
		execute_node(node->right);
	return (exit_status);
}
