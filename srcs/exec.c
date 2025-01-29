/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/01/29 12:59:37 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_bintree *node)
{
	int	fd_in;
	int	fd_out;
	int i;
	char *name;
	t_type_rdir type;
	
	i = -1;
	while (node->cmd->rdir[++i].name)
	{
		type = node->cmd->rdir[i].type;
		name = node->cmd->rdir[i].name;
		if (type == R_OUT || type == APPEND)
		{
			if (type == APPEND)
				fd_out = open(name, O_CREAT | O_WRONLY | O_APPEND, 0777);
			else
				fd_out = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			dup2(fd_out, node->stdfd[OUT]);
			close(fd_out);
		}
		if (type == R_IN || type == HEREDOC)
		{
			fd_in = open(name, O_RDONLY, 0777);
			dup2(fd_in, node->stdfd[IN]);
			close(fd_in);
		}
	}
	return (0);
}

void	child_process(t_bintree *node, t_data *data)
{
	dup2(node->stdfd[IN], 0);
	dup2(node->stdfd[OUT], 1);
	close(node->stdfd[IN]);
	close(node->stdfd[OUT]);
	execve(node->cmd->args[0], node->cmd->args, data->envp);
	perror("minishell is warning you");
	exit(127);
}

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "env"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (1);
	return (0);
}

int	exec_builtin(t_bintree *node, t_data *data)
{
	if (data->flag)
	{
		ft_putstr_fd("exec builtins: ", 2);
		ft_putendl_fd(node->cmd->args[0], 2);
	}
//	if (!ft_strcmp(node->cmd->args[0], "cd"))
//		change_dir(node, data);
	if (!ft_strcmp(node->cmd->args[0], "pwd"))
		print_working_dir(node, data);
	if (!ft_strcmp(node->cmd->args[0], "export"))
		export(node, data);
	if (!ft_strcmp(node->cmd->args[0], "env"))
		print_env(node, data->envp, "");
	/* if (!ft_strcmp(node->cmd->args[0], "unset")) */
	/* 	unset(node, data); */
	if (!ft_strcmp(node->cmd->args[0], "echo"))
		echo(node, data);
	if (!ft_strcmp(node->cmd->args[0], "exit"))
	{
		printf("exit");
		free_minishell(data);
		exit(0);
	}

	return (0);
}

int	exec_cmd(t_bintree *node, t_data *data)
{
	int pid;
	int exit_status;

	redir(node);
	if (is_builtin(node->cmd))
	{
		exit_status = exec_builtin(node, data);
		close(node->stdfd[IN]);
		close(node->stdfd[OUT]);
		return (exit_status);
	}
	if (!build_cmd(node, data))
		pid = fork();
	else
	{
		perror("not a cmd");
		return (127); // if dont find the command with access
	}
	if (!pid)
		child_process(node, data);
	close(node->stdfd[IN]);
	close(node->stdfd[OUT]);
	waitpid(-1, &exit_status, 0);
	data->status = WEXITSTATUS(exit_status);
	if (data->flag)
		printf("Exit status of %s is %d\n", node->input, exit_status);
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
		exit_status = exec_cmd(node, data);
	return (exit_status);
}
