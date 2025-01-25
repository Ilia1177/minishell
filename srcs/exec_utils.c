/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:14:26 by ilia              #+#    #+#             */
/*   Updated: 2025/01/25 15:26:00 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tab_dup(char **tab)
{
	char	**new;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	tab[i] = NULL;
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
			env[i] += 5;
			paths = ft_split(env[i], ':');
			env[i] -= 5;
			return (paths);
		}
		i++;
	}
	return (paths);
}

char	*get_full_path(char **paths, char *str)
{
	int		i;
	char	*full_path;
	char	*cmd;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strnlen(str, ' ') + 1));
	i = -1;
	while (++i < (int)ft_strnlen(str, ' '))
		tmp[i] = str[i];
	tmp[i] = '\0';
	cmd = ft_strjoin("/", tmp);
	free(tmp);
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

int	build_cmd(t_bintree *node, t_data *data)
{
	char 	*cmd_name;
	
//	cmd_name = node->content[0];
//	node->content[0] = get_full_path(data->paths, cmd_name);
//	free(cmd_name);
	cmd_name = node->cmd->args[0];
	node->cmd->args[0] = get_full_path(data->paths, cmd_name);
	free(cmd_name);
	if (!node->content[0])
	{
		data->status = 127;
		return (-1);
	}
	return (0);
}
