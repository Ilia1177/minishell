/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:24:42 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/13 17:05:44 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwds(t_data *data)
{
	char	wd[1024];
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_strjoin("OLDPWD=", catch_expand(data, "PWD"));
	update_envp(data, old_pwd);
	free(old_pwd);
	getcwd(wd, sizeof(wd));
	new_pwd = ft_strjoin("PWD=", wd);
	update_envp(data, new_pwd);
	free(new_pwd);
}

char	*make_cd_path(char *dir_name)
{
	char	wd[1024];
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = NULL;
	getcwd(wd, sizeof(wd));
	tmp = ft_strjoin(wd, "/");
	path = ft_strjoin(tmp, dir_name);
	free(tmp);
	return (path);
}

int	change_dir(t_bintree *node, t_data *data)
{
	char	*path;

	path = NULL;
	if (node->cmd->args[1] && node->cmd->args[2])
	{
		ft_printf(2, TM_ARG, "cd");
		return (1);
	}
	else if (!node->cmd->args[1] || !ft_strcmp(node->cmd->args[1], "--"))
		path = ft_strdup(catch_expand(data, "HOME"));
	else if (!ft_strcmp(node->cmd->args[1], "-"))
		path = ft_strdup(catch_expand(data, "OLDPWD"));
	else if (node->cmd->args[1][0] == '/')
		path = ft_strdup(node->cmd->args[1]);
	else
		path = make_cd_path(node->cmd->args[1]);
	if (!chdir(path))
		update_pwds(data);
	else
	{
		ft_printf(2, NFD_MSG);
		data->status = 1;
	}
	free(path);
	return (data->status);
}
