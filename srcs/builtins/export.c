/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:07 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/14 13:32:58 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_entry(char *name, char *value)
{
	char	*tmp;
	char	*line;

	if (!name)
	{
		free(value);
		return (NULL);
	}
	tmp = name;
	name = ft_strjoin(name, "=");
	free(tmp);
	if (!name)
		return (NULL);
	if (!value || !value[0])
		line = name;
	else
	{
		line = ft_strjoin(name, value);
		free(name);
		if (!line)
		{
			free(value);
			return (NULL);
		}
	}
	free(value);
	return (line);
}

char	**set_env(char *name, char *value, char **old_envp)
{
	int		i;
	char	*line;
	char	**new_env;

	line = new_entry(name, value);
	if (!line)
		return (old_envp);
	if (!old_envp)
	{
		new_env = malloc(sizeof(char *) * (2));
		if (!new_env)
			return (old_envp);
		new_env[0] = line;
		new_env[1] = NULL;
		return (new_env);
	}
	i = 0;
	while (old_envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (old_envp);
	i = -1;
	while (old_envp[++i])
		new_env[i] = old_envp[i];
	new_env[i] = line;
	new_env[++i] = NULL;
	free(old_envp);
	return (new_env);
}

int	update_envp(t_data *data, char *str)
{
	char	*tmp;
	char	*name;
	char	*value;
	int		at_index;
	int		error;

	error = catch_name(&name, str);
	if (!error)
	{
		value = catch_value(str);
		at_index = exist(data->envp, name);
		if (at_index >= 0)
		{
			tmp = data->envp[at_index];
			data->envp[at_index] = new_entry(name, value);
			free(tmp);
		}
		else
			data->envp = set_env(name, value, data->envp);
	}
	else
	{
		free(name);
		if (error == 1)
			ft_printf(2, "msh: export: %s\"%s\n", name, WARNING);
		else if (error == 2)
			return (0);
	}
	return (error);
}

int	export(t_bintree *node, t_data *data)
{
	int	j;
	int	status;

	if (node->pipefd[OUT] == -2 || node->pipefd[IN] == -2)
		return (1);
	status = 0;
	j = 1;
	if (!node->cmd->args[j])
		print_env(node, data->envp, "declare -x ");
	while (node->cmd->args[j])
	{
		if (update_envp(data, node->cmd->args[j]))
			status = 1;
		j++;
	}
	data->status = status;
	return (data->status);
}
