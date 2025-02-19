/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:13:48 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 19:21:23 by jhervoch         ###   ########.fr       */
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

int	redir(t_bintree *node)
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
		{
			perror("msh");
			return (status);
		}
	}
	return (0);
}

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (!path)
		return (0);
	if (access(path, F_OK) == 0)
	{
		if (stat(path, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
			{
				ft_printf(2, "msh: Is a directory\n");
				return (126);
			}
		}
	}
	return (0);
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
