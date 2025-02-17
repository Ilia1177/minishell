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

int		change_dir(t_bintree *node, t_data *data)
{
	char	wd[1024];
	char	*path;
	char 	*tmp;
	int		i;

	i = 0;
	while (node->cmd->args[i])
		i++;
	if (!node->cmd->args[1] || i > 2)
		return (1);
	if (!ft_strcmp(node->cmd->args[1], "-"))
		path = ft_strdup(catch_expand(data, "OLDPWD"));
	else if (!ft_strcmp(node->cmd->args[1], "--"))
		path = ft_strdup(catch_expand(data, "HOME"));
	else if (node->cmd->args[1][0] == '/')
		path = ft_strdup(node->cmd->args[1]);
	else
	{
		getcwd(wd, sizeof(wd));
		tmp = ft_strjoin(wd, "/");
		path = ft_strjoin(tmp, node->cmd->args[1]);
		free(tmp);
	}
	if (!chdir(path))
		update_pwds(data);
	else
	{
		ft_printf(2, "M!N!$H3LL: cd: include: No such file or directory\n");
		data->status = 1;
	}
	free(path);
	return (data->status);
}
