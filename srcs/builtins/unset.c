/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:09:29 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/14 17:19:17 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**unset_env(char *name, t_data *data)
{
	int		i;
	int		j;
	int		env_index;
	char	**new_env;

	env_index = exist(data->envp, name);
	if (env_index == -1)
		return (data->envp);
	i = 0;
	while (data->envp[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (data->envp);
	free(data->envp[env_index]);
	i = -1;
	j = -1;
	while (data->envp[++i])
	{
		if (i == env_index)
			i++;
		new_env[++j] = data->envp[i];
	}
	new_env[++j] = NULL;
	free(data->envp);
	return (new_env);
}

int	unset(t_bintree *node, t_data *data)
{
	int	i;

	i = 1;
	if (!node->cmd->args[i])
		return (0);
	while (node->cmd->args[i])
	{
		data->envp = unset_env(node->cmd->args[i], data);
		i++;
	}
	return (0);
}
