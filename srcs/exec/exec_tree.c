/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:10:29 by npolack           #+#    #+#             */
/*   Updated: 2025/02/14 13:54:49 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_tree(t_data *data)
{
	int	status;
	int	save_status;
	pid_t	wpid;

	data->paths = get_paths(data->envp); 
	if (data->flag)
		ft_printf(2, "PATHS = %p\n", data->paths);
	data->tree->stdfd[IN] = dup(0);
	data->tree->stdfd[OUT] = dup(1);
	status = execute_node(data->tree, data);
	close_fd(data->tree);
	if (data->flag)
		ft_printf(2, "Status of exec_tree: %d\n", data->status);
	if (data->pid == -2) 
	{ 
		while(waitpid(-1, NULL, WUNTRACED) != -1)
			;
		return (status);
	}
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

int	make_pipe(t_bintree *node, t_data *data)
{
	int	exit_status;
  
	pipe(node->pipefd);	
	
	node->left->stdfd[OUT] = dup(node->pipefd[OUT]);
	node->left->stdfd[IN] = dup(node->stdfd[IN]);
	node->left->pipefd[IN] = -2;
	node->left->pipefd[OUT] = -2;
	exit_status = execute_node(node->left, data);
	if (node->right)
	{
		node->right->pipefd[IN] = -2;
		node->right->pipefd[OUT] = -2;
		node->right->stdfd[OUT] = dup(node->stdfd[OUT]);
		node->right->stdfd[IN] = dup(node->pipefd[IN]);
		exit_status = execute_node(node->right, data);
	}
	close_fd(node);
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
			close_fd(node);
			exit_status = execute_node(node->right, data);
		}
		else
		{
			close_fd(node);
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
