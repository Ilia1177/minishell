/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:23:44 by npolack           #+#    #+#             */
/*   Updated: 2025/02/19 19:15:33 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "builtins.h"

static void	child_process(t_bintree *node, t_data *data)
{
	dup2(node->stdfd[IN], 0);
	dup2(node->stdfd[OUT], 1);
	close_fd_tree(data->tree);
	execve(node->cmd->args[0], node->cmd->args, data->envp);
	perror("msh: shit happened");
	free_minishell(data, 1);
}

static int	is_builtin(t_cmd *cmd)
{
	if (!cmd->args[0])
		return (0);
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

	if (data->flag)
		ft_printf(2, "--> exec_cmd\n");
	data->pid = -2;
	exit_status = redir(node);
	if (!node->input || !node->input[0])
	{
		close_fd(node);
		return (exit_status);
	}
	if (!exit_status && is_builtin(node->cmd))
		exit_status = exec_builtin(node, data);
	else if (!exit_status)
		exit_status = build_cmd(node, data);
	if (exit_status || is_builtin(node->cmd))
	{
		close_fd(node);
		return (exit_status);
	}
	data->pid = fork();
	if (!data->pid)
		child_process(node, data);
	close_fd(node);
	return (-1);
}
