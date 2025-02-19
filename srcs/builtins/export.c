/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:37:07 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 18:03:59 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

char	**new_to_env(char *name, char *value, char **old_envp)
{
	int		i;
	char	*line;
	char	**new_env;

	if (value[0] == '+')
		value++;
	line = ft_strjoin(name, value);
	if (!line)
		return (old_envp);
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

int	add_to_env(char *name, char *input, t_data *data)
{
	char	*tmp;
	int		at_index;

	if (!name || !input)
		return (-1);
	tmp = NULL;
	input += ft_strlen(name);
	at_index = exist(data->envp, name);
	if (at_index < 0)
		data->envp = new_to_env(name, input, data->envp);
	else
	{
		tmp = data->envp[at_index];
		if (at_index >= 0 && *input == '=')
			data->envp[at_index] = ft_strjoin(name, input);
		else if (at_index >= 0 && *input == '+')
			data->envp[at_index] = ft_strjoin(data->envp[at_index], input + 2);
		if (!data->envp[at_index])
		{
			data->envp[at_index] = tmp;
			return (-1);
		}
		free(tmp);
	}
	return (0);
}

int	update_envp(t_data *data, char *str)
{
	char	*name;
	int		error;

	error = catch_name(&name, str);
	if (!error && name)
	{
		if (add_to_env(name, str, data))
			error = -1;
	}
	else if (error == 1)
		ft_printf(2, "msh: export: %s\"%s\n", name, WARNING);
	else if (error == -1)
		error = 0;
	free(name);
	return (error);
}

int	export(t_bintree *node, t_data *data)
{
	int	j;
	int	status;

	status = 0;
	j = 1;
	if (!node->cmd->args[j])
		print_env(node, data->envp, "declare -x ");
	else if (node->pipefd[OUT] == -2 || node->pipefd[IN] == -2)
		return (1);
	while (node->cmd->args[j])
	{
		if (update_envp(data, node->cmd->args[j]))
			status = 1;
		j++;
	}
	data->status = status;
	return (data->status);
}
