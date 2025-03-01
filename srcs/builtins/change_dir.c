/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:24:42 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 23:31:19 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "builtins.h"

static void	update_pwds(t_data *data)
{
	char	wd[1024];
	char	*old_pwd;
	char	*new_pwd;

	if (exist(data->envp, "OLDPWD") != -1)
	{
		old_pwd = ft_strjoin("OLDPWD=", catch_expand(data, "PWD"));
		update_envp(data, old_pwd);
		free(old_pwd);
	}
	if (exist(data->envp, "PWD") != -1)
	{
		if (getcwd(wd, sizeof(wd)))
		{
			new_pwd = ft_strjoin("PWD=", wd);
			if (!new_pwd)
				return ;
			update_envp(data, new_pwd);
			free(new_pwd);
		}
	}
}

char	*make_cd_path(char *dir_name)
{
	char	wd[1024];
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = NULL;
	if (getcwd(wd, sizeof(wd)))
	{
		tmp = ft_strjoin(wd, "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, dir_name);
		free(tmp);
	}
	return (path);
}

int	change_dir(t_bintree *node, t_data *data)
{
	char	*path;

	path = NULL;
	if (!node->cmd->args[1])
		return (0);
	if (node->cmd->args[1] && node->cmd->args[2])
	{
		ft_printf(2, TM_ARG, "cd");
		return (1);
	}
	else if (node->cmd->args[1][0] == '/')
		path = ft_strdup(node->cmd->args[1]);
	else
		path = make_cd_path(node->cmd->args[1]);
	if (path && !chdir(path))
		update_pwds(data);
	else
	{
		ft_printf(2, NOENT_MSG, "cd");
		data->status = 1;
	}
	free(path);
	return (data->status);
}
