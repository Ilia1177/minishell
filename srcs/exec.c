/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/01/23 20:30:30 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_bintree *node)
{
	int	fd_in;
	int	fd_out;

	if (node->rdir_out)
	{
		fd_out = open(node->rdir_out, O_CREAT | O_WRONLY | O_APPEND, 0777);
		dup2(fd_out, node->stdfd[OUT]);
		close(fd_out);
	}
	if (node->rdir_in)
	{
		fd_in = open(node->rdir_in, O_RDONLY, 0777);
		dup2(fd_in, node->stdfd[IN]);
		close(fd_in);
	}
	return (0);
}

int	exec_cmd(t_bintree *node, t_data *data)
{
	int pid;
	int exit_status;

	redir(node);
	if (!build_cmd(node, data))
		pid = fork();
	else
	{
		perror("not a cmd");
		return (127); // if dont find the command with access
	}
	if (!pid)
	{
		dup2(node->stdfd[IN], 0);
		dup2(node->stdfd[OUT], 1);
		close(node->stdfd[IN]);
		close(node->stdfd[OUT]);
		execve(node->content[0], node->content, data->envp);
		perror("minishell is warning you");
		exit(-1);
	}
	close(node->stdfd[IN]);
	close(node->stdfd[OUT]);
	waitpid(-1, &exit_status, 0);
	data->status = WEXITSTATUS(exit_status);
	printf("Exit status of %s is %d\n", node->content[0], exit_status);
	return (exit_status);
}


int	execute_tree(t_data *data)
{
	int	exit_status;

	data->paths = get_paths(data->envp); //malloc char**
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

int	make_operation(t_bintree *node, t_data *data)
{
	int	exit_status;

	node->left->stdfd[IN] = dup(node->stdfd[IN]);
	node->left->stdfd[OUT] = dup(node->stdfd[OUT]);
	exit_status = execute_node(node->left, data);
	if (!ft_strcmp(node->content[0], "||"))
	{	
		if (exit_status && node->right)
		{
			node->right->stdfd[IN] = dup(node->stdfd[IN]);
			node->right->stdfd[OUT] = dup(node->stdfd[OUT]);
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
		node->right->stdfd[IN] = dup(node->stdfd[IN]);
		node->right->stdfd[OUT] = dup(node->stdfd[OUT]);
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
		exit_status = exec_cmd(node, data);
	return (exit_status);
}
