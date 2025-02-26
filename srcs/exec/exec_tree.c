/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:10:29 by npolack           #+#    #+#             */
/*   Updated: 2025/02/26 23:52:45 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	get_child_status(t_data *data)
{
	int	save_status;
	int	status;
	int	wpid;

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
	if (data->flag)
		ft_printf(2, "child_status: %d\n", status);
	return (status);
}

int	execute_tree(t_data *data)
{
	int		status;

	data->paths = get_paths(data->envp);
	if (data->flag)
		ft_printf(2, "--> execute_tree\nPATHS = %p\n", data->paths);
	data->tree->stdfd[IN] = dup(0);
	data->tree->stdfd[OUT] = dup(1);
	status = execute_node(data->tree, data);
	close_fd(data->tree);
	if (data->flag)
		ft_printf(2, "execute_tree: status: %d\n", status);
	if (data->pid == -2)
	{
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		return (status);
	}
	status = get_child_status(data);
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

int	make_operation(t_bintree *node, t_data *data)
{
	int	exit_status;

	connect_stdio(node, node->left);
	exit_status = execute_node(node->left, data);
	if (!exit_status)
		exit_status = get_child_status(data);
	if (!ft_strcmp(node->input, "||"))
	{
		if (exit_status)
		{
			connect_stdio(node, node->right);
			exit_status = execute_node(node->right, data);
		}
	}
	else if (!exit_status)
	{
		connect_stdio(node, node->right);
		exit_status = execute_node(node->right, data);
	}
	close_fd(node);
	return (exit_status);
}

int	execute_node(t_bintree *node, t_data *data)
{
	int	exit_status;

	if (data->flag)
		ft_printf(2, "--> execute_node: %s\n", node->input);
	if (node->left)
	{
		if (node->type == PIPE)
			exit_status = make_pipe(node, data);
		else
			exit_status = make_operation(node, data);
		return (exit_status);
	}
	else
		exit_status = exec_cmd(node, data);
	return (exit_status);
}
