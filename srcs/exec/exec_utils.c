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

int	find_cmd_in_paths(char *str, t_bintree *node, t_data *data)
{
	int		i;
	char	*full_path;
	char	*cmd;

	if (data->flag)
		ft_printf(2, "find_cmd_in_path\n");
	if (!data->paths || !str)
		return (127);
	cmd = ft_strjoin("/", str);
	if (!cmd)
		return (-1);
	i = -1;
	while (data->paths[++i])
	{
		full_path = ft_strjoin(data->paths[i], cmd);
		if (!full_path)
		{
			free(cmd);
			return (-1);
		}
		if (!access(full_path, F_OK))
		{
			if (data->flag)
				ft_printf(2, "command found at %s\n", full_path);
			node->cmd->args[0] = full_path;
			free(cmd);
			return (0);
		}
		free(full_path);
	}
	free(cmd);
	return (127);
}


int	find_cmd_in_pwd(char *cmd_name, t_bintree *node, t_data *data) 
{
	char	*tmp;
	char	*pwd;
	int		status;

	if (data->flag)
		ft_printf(2, "Look for command with pwd\n");
	if (!cmd_name || !cmd_name[0])
		return (-1);
	node->cmd->args[0] = NULL;
	status = 0;
	tmp = ft_strjoin(catch_expand(data, "PWD"), "/");
	pwd = ft_strjoin(tmp, cmd_name);
	free(tmp);
	if (!pwd)
		status = -1;
	else if (!access(pwd, F_OK))
	{
		node->cmd->args[0] = pwd;
		return (0);
	}
	else
		status = 127;
	free(pwd);
	return (status);
}

int	is_directory(char *path)
{
	struct stat statbuf;

	if (!path)
		return (0);
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
	if (!node->cmd->args[0] || !node->cmd->args[0][0])
		return (127);
	cmd_name = node->cmd->args[0];
	if (is_directory(cmd_name))
		return (126);
	// look for executable in current dir if it is a path or formated with ./script at begining of cmd_name
	else if (!ft_strncmp(cmd_name, "./", 2) || ft_strchr(cmd_name, '/'))
		status = find_cmd_in_pwd(cmd_name, node, data);
	// look for executable in current dir formated script with PATH unset
	else if (!data->paths)
		status = find_cmd_in_pwd(cmd_name, node, data);
	// look for the executable in paths in others cases
	else
		status = find_cmd_in_paths(cmd_name, node, data);
	if (status)
		node->cmd->args[0] = cmd_name;
	else
		free(cmd_name);
	if (errno == EACCES && status == 127)
	{
		perror("msh");
		status = 126;
	}
	else if (status == 127)
		ft_printf(2, "msh: %s: command not found\n", node->cmd->args[0]);
	if (data->flag)
		ft_printf(2, "full commande is %s\n", node->cmd->args[0]);
	return (status);
}
