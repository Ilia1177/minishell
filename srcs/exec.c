/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 21:08:30 by npolack          ###   ########.fr       */
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

int	pipe_operation()
{
	int	pid;

	pid = fork();
	if (!pid)
	
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

int	execute_tree(t_bintree *node, t_data *data)
{
	int	exit_status;
	int	pid;

	if (node->type = PIPE)
	{
		dup2(stdfd[0], 0);
		exit_status = pipe_operation();
	}
	if (node->left)
		exit_status = execute_tree(node->left);

	if (node->type = OPERATOR)
		exit_status = make_operation(node, data);
	else if (node->type = CMD)
		exit_status = exec_cmd(node, data);

	if (!exit_status && node->right)
		execute_tree(node->right);
	return (exit_status);
}
