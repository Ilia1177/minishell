/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:14:26 by ilia              #+#    #+#             */
/*   Updated: 2025/02/26 16:31:44 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "exec.h"

t_cmd	*cmddup(t_cmd *cmd)
{
	t_cmd	*new_cmd;
	t_rdir	*new_rdir;
	int		i;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->args = tab_dup(cmd->args);
	i = 0;
	if (cmd->rdir)
	{
		while (cmd->rdir[i].name)
			i++;
		new_rdir = malloc(sizeof(t_cmd) * (i + 1));
		if (!new_rdir)
			return (NULL);
		i = 0;
		while (cmd->rdir[i].name)
		{
			new_cmd->rdir[i] = cmd->rdir[i];
			i++;
		}
		new_cmd->rdir[i].name = NULL;
	}
	return (new_cmd);
}

char	**tab_dup(char **tab)
{
	char	**new;
	int		i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	find_cmd_in_paths(char *str, t_bintree *node, t_data *data)
{
	int		i;
	char	*full_path;
	char	*cmd;
	int		status;

	if (data->flag)
		ft_printf(2, "--> find_cmd_in_paths\n");
	if (!data->paths || !str)
		return (127);
	status = 0;
	cmd = ft_strjoin("/", str);
	if (!cmd)
		return (-1);
	i = -1;
	while (data->paths[++i])
	{
		full_path = ft_strjoin(data->paths[i], cmd);
		if (!full_path)
			break ;
		if (!access(full_path, F_OK | X_OK))
		{
			free(cmd);
			node->cmd->args[0] = full_path;
			return (0);
		}
		else if (errno == EACCES || is_directory(full_path))
		{
			free(cmd);
			return (126);
		}
		else
			status = 127;
		free(full_path);
	}
	free(cmd);
	return (status);
}

int	find_cmd_in_pwd(char *cmd_name, t_bintree *node, t_data *data)
{
	char	*tmp;
	char	*pwd;
	int		status;

	if (data->flag)
		ft_printf(2, "--> find_cmd_in_pwd\n");
	if (!cmd_name || !cmd_name[0])
		return (-1);
	if (is_directory(cmd_name))
		return (126);
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
	else if (errno == EACCES || is_directory(pwd))
		status = 126;
	else
		status = 127;
	free(pwd);
	return (status);
}

//if (status = 0) commande will be execute by execve
int	save_build_cmd(t_bintree *node, t_data *data)
{
	char	*cmd_name;
	int		status;

	status = 0;
	if (!node->cmd || !node->cmd->args[0] || !node->cmd->args[0][0])
		return (127);
	cmd_name = node->cmd->args[0];

	if (!ft_strcmp(".", cmd_name)) // ||  ft_strcmp("..", cmd_name))
		status = 2;
	else if (!data->paths && ft_strncmp("/", cmd_name, 1))
	{
		cmd_name = ft_strjoin("./", cmd_name);
		free(node->cmd->args[0]);
		status = find_cmd_in_pwd(cmd_name, node, data);
		if (!status)
			free(cmd_name);
		ft_printf(2, "get in 1\n");
	}
	else if (ft_strchr(cmd_name, '/') && !access(cmd_name, X_OK) && !is_directory(cmd_name))
	{
		ft_printf(2, "get in 2\n");
		status = 0;
	}
	else if (ft_strchr(cmd_name, '/') && is_directory(cmd_name))
	{
		ft_printf(2, "get in 3\n");
		status = 126;
	}
	else if (!is_directory(cmd_name)) 
	{
		status = find_cmd_in_paths(cmd_name, node, data);
		ft_printf(2, "get in 4: status: %d\n", status);
		if (status && !ft_strncmp("./", cmd_name, 2))
			status = find_cmd_in_pwd(cmd_name, node, data);
		ft_printf(2, "get in 4: status: %d\n", status);
		if (!status)
			free(cmd_name);
		else
			node->cmd->args[0] = cmd_name;
	}
	if (!status && is_directory(cmd_name))
		status = 127;
	if (status == 2)
		ft_printf(2, "msh: %s: filename argument required\n", node->cmd->args[0]);
	else if (status == 126 && !is_directory(node->cmd->args[0]))
		perror("msh");
	else if (status == 127)
		ft_printf(2, "msh: %s: command not found\n", node->cmd->args[0]);
	else if (is_directory(node->cmd->args[0]))
		ft_printf(2, "msh: is a directory\n");
	return (status);
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
	{
		if (!access(cmd_name, X_OK | F_OK) && !is_directory(cmd_name))
			status = 0;
		else if (errno == EACCES || is_directory(cmd_name))
			status = 126;
		else
			status = 127;
	}
	else
	{
		if (!data->paths)
			status = find_cmd_in_pwd(cmd_name, node, data);
		else
			status = find_cmd_in_paths(cmd_name, node, data);
	}
	if (status == 2)
		ft_printf(2, "msh: %s: filename argument required\n", node->cmd->args[0]);
	if (errno == ENOENT && ft_strchr(cmd_name, '/'))
		ft_printf(2, "no such file\n");
	else if (status == 127)
		ft_printf(2, "cmd not found\n");
	else if (status == 126 && !is_directory(cmd_name))
		ft_printf(2, "perms denied\n");
	else if (status == 126)
		ft_printf(2, "is directory\n");
	if (!status && !ft_strchr(cmd_name, '/') && ft_strcmp(cmd_name, "..") && ft_strcmp(cmd_name, ".."))
			free(cmd_name);
	return (status);
}
