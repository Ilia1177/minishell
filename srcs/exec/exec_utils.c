/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:14:26 by ilia              #+#    #+#             */
/*   Updated: 2025/02/14 22:08:28 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_paths(char **env)
{
	char	**paths;
	int		i;

	if (!env)
		return (NULL);
	paths = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			if (!env[i][5])
				return (NULL);
			paths = ft_split(env[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_full_path(char **paths, char *str)
{
	int		i;
	char	*full_path;
	char	*cmd;

	if (!paths)
		return (NULL);
	cmd = ft_strjoin("/", str);
	if (!cmd)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!access(full_path, X_OK))
		{
			free(cmd);
			return (full_path);
		}
		free(full_path);
	}
	free(cmd);
	return (NULL);
}

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

int	try_with_pwd(t_bintree *node, t_data *data, char *cmd_name)
{
	char	*tmp;
	char	*pwd;
	int		status;

	node->cmd->args[0] = cmd_name;
	status = 0;
	tmp = ft_strjoin(catch_expand(data, "PWD"), "/");
	pwd = ft_strjoin(tmp, cmd_name);
	free(tmp);
	if (!pwd)
		status = 127;
	else if (!access(pwd, X_OK))
	{
		node->cmd->args[0] = pwd;
		free(cmd_name);
	}
	else
	{
		node->cmd->args[0] = cmd_name;
		free(pwd);
		status = 127;
	}
	return (status);
}

int	is_directory(char *path)
{
	struct stat statbuf;

	if (access(path, F_OK) == 0)
	{
		if (stat(path, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
			{
				ft_printf(2, "Is a directory\n");
				return (126);
			}
		}
	}
	return (0);
}

int	build_cmd(t_bintree *node, t_data *data)
{
	char	*cmd_name;
	int		status;

	status = 0;
	if (!node->cmd->args[0][0])
		return (127);
	cmd_name = node->cmd->args[0];
	node->cmd->args[0] = get_full_path(data->paths, cmd_name);
	if (!node->cmd->args[0])
		status = try_with_pwd(node, data, cmd_name);
	else
		free(cmd_name);
	if (status && is_directory(node->cmd->args[0]))
		return (126);
	if (status && !access(node->cmd->args[0], X_OK))
		return (0);
	if (errno == EACCES && status == 127)
	{
		perror("msh");
		status = 126;
	}
	else if (status == 127)
		ft_printf(2, "msh: %s: command not found\n", node->cmd->args[0]);
	return (status);
}
