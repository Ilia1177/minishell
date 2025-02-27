/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:14:26 by ilia              #+#    #+#             */
/*   Updated: 2025/02/27 12:01:08 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "exec.h"

int	find_cmd_in_pwd(char *cmd_name, t_bintree *node, t_data *data)
{
	char	*tmp;
	char	*pwd;
	int		status;

	if (!cmd_name || !cmd_name[0])
		return (-1);
	node->cmd->args[0] = NULL;
	status = 0;
	tmp = ft_strjoin(catch_expand(data, "PWD"), "/");
	pwd = ft_strjoin(tmp, cmd_name);
	free(tmp);
	if (!pwd)
		status = 1;
	else if (!access(pwd, F_OK | X_OK))
	{
		node->cmd->args[0] = pwd;
		return (0);
	}
	else if (errno == EACCES || is_directory(pwd) || is_directory(cmd_name))
		status = 126;
	else
		status = 127;
	free(pwd);
	return (status);
}

static void	print_status(t_bintree *node, char *cmd_name, int status)
{
	if (status == 2)
		ft_printf(2, FAR_MSG, node->cmd->args[0]);
	else if (cmd_name && errno == ENOENT && ft_strchr(cmd_name, '/'))
		ft_printf(2, NOENT_MSG, node->cmd->args[0]);
	else if (status == 127)
		ft_printf(2, CMDNF_MSG, node->cmd->args[0]);
	else if (cmd_name && status == 126 && !is_directory(cmd_name))
		ft_printf(2, PERMD_MSG, node->cmd->args[0]);
	else if (status == 126)
		ft_printf(2, ISDIR_MSG, node->cmd->args[0]);
}

static void	find_cmd(t_bintree *node, t_data *data, char *cmd_name, int *status)
{
	if (!data->paths)
		*status = find_cmd_in_pwd(cmd_name, node, data);
	else
		*status = find_cmd_in_paths(cmd_name, node, data);
	if (*status == 0)
		free(cmd_name);
	else
		node->cmd->args[0] = cmd_name;
}

static void	access_command(char *cmd_name, int *status)
{
	if (!access(cmd_name, X_OK | F_OK) && !is_directory(cmd_name))
		*status = 0;
	else if (errno == EACCES || is_directory(cmd_name))
		*status = 126;
	else
		*status = 127;
}

int	build_cmd(t_bintree *node, t_data *data)
{
	char	*cmd_name;
	int		status;

	status = 0;
	if (!node->cmd || !node->cmd->args[0] || !node->cmd->args[0][0])
		return (127);
	cmd_name = node->cmd->args[0];
	if (!ft_strcmp(cmd_name, "."))
		status = 2;
	else if (!ft_strcmp(cmd_name, ".."))
		status = 127;
	else if (ft_strchr(cmd_name, '/'))
		access_command(cmd_name, &status);
	else
	{
		find_cmd(node, data, cmd_name, &status);
		if (!status)
			cmd_name = NULL;
	}
	print_status(node, cmd_name, status);
	return (status);
}
