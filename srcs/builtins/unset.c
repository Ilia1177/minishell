/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:09:29 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/14 13:02:40 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**unset_env(char *name, char **old_envp)
{
	int		i;
	int		j;
	int		env_index;
	char	**new_env;

	env_index = exist(old_envp, name);
	if (env_index == -1)
		return (old_envp);
	i = 0;
	while (old_envp[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (old_envp);
	i = -1;
	j = -1;
	while (old_envp[++i])
	{
		if (i == env_index)
		{
			free(old_envp[i]); // recently added (Nil) still leaks...
			i++;
		}
		new_env[++j] = old_envp[i];
	}
	new_env[j] = NULL;
	free(old_envp);
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
		data->envp = unset_env(node->cmd->args[1], data->envp);
		i++;
	}
	return (0);
}
