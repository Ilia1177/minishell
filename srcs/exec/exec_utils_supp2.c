/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_supp2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:55:24 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/26 20:52:01 by jhervoch         ###   ########.fr       */
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

static int	access_path(char **command, t_bintree *node, char *path, int status)
{
	char	*full_path;
	char	*cmd;

	cmd = *command;
	full_path = ft_strjoin(path, cmd);
	if (!full_path)
		return (-1);
	if (!access(full_path, F_OK | X_OK))
	{
		node->cmd->args[0] = full_path;
		return (0);
	}
	else if (errno == EACCES || is_directory(full_path))
	{
		return (126);
	}
	else
		status = 127;
	free(full_path);
	return (status);
}

int	find_cmd_in_paths(char *str, t_bintree *node, t_data *data)
{
	int		i;
	char	*cmd;
	int		status;

	if (!data->paths || !str)
		return (127);
	status = 0;
	cmd = ft_strjoin("/", str);
	if (!cmd)
		return (-1);
	i = -1;
	while (data->paths[++i])
	{
		status = access_path(&cmd, node, data->paths[i], status);
		if (status != 127)
			break ;
	}
	free(cmd);
	return (status);
}
