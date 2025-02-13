/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/02/13 17:45:23 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_rdir(t_bintree *node, char *name, t_type_rdir type)
{
	int			fd_in;
	int			fd_out;

	if (type == R_OUT || type == APPEND)
	{
		if (type == APPEND)
			fd_out = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			return (1);
		dup2(fd_out, node->stdfd[OUT]);
		close(fd_out);
	}
	if (type == R_IN || type == HEREDOC)
	{
		fd_in = open(name, O_RDONLY, 0644);
		if (fd_in == -1)
			return (1);
		dup2(fd_in, node->stdfd[IN]);
		close(fd_in);
	}
	return (0);
}

static int	redir(t_bintree *node)
{
	int			i;
	int			status;
	char		*name;
	t_type_rdir	type;

	i = -1;
	while (node->cmd->rdir[++i].name)
	{
		type = node->cmd->rdir[i].type;
		name = node->cmd->rdir[i].name;
		status = open_rdir(node, name, type);
		if (status)
			return (status);
	}
	return (0);
}

static void	child_process(t_bintree *node, t_data *data)
{
	dup2(node->stdfd[IN], 0);
	dup2(node->stdfd[OUT], 1);
	close_fd_tree(data->tree);
	execve(node->cmd->args[0], node->cmd->args, data->envp);
	perror("msh: Big shit happened");
	kill(0, SIGINT);
	exit_minishell(node, data);
}

static int	is_builtin(t_cmd *cmd)
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

static int	exec_builtin(t_bintree *node, t_data *data)
{
	int	status;

	if (data->flag)
		ft_printf(2, "Execute builtin command: %s\n", node->cmd->args[0]);
	if (!ft_strcmp(node->cmd->args[0], "cd"))
		status = change_dir(node, data);
	if (!ft_strcmp(node->cmd->args[0], "pwd"))
		status = print_working_dir(node, data);
	if (!ft_strcmp(node->cmd->args[0], "export"))
		status = export(node, data);
	if (!ft_strcmp(node->cmd->args[0], "env"))
		status = print_env(node, data->envp, "");
	if (!ft_strcmp(node->cmd->args[0], "unset"))
		status = unset(node, data);
	if (!ft_strcmp(node->cmd->args[0], "echo"))
		status = echo(node, data);
	if (!ft_strcmp(node->cmd->args[0], "exit"))
		status = exit_minishell(node, data);
	return (status);
}

int	exec_cmd(t_bintree *node, t_data *data)
{
	int	exit_status;

	exit_status = redir(node);
	if (!exit_status && is_builtin(node->cmd))
		exit_status = exec_builtin(node, data);
	else if (!exit_status)
		exit_status = build_cmd(node, data);
	if (exit_status || is_builtin(node->cmd))
	{
		data->pid = -1;
		close_fd(node);
		return (exit_status);
	}
	data->pid = fork();
	if (!data->pid)
		child_process(node, data);
	close_fd(node);
	return (-1);
}
