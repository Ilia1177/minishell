/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:09:29 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/15 11:18:40 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tablen(char **tab)
{
	int	len;
	
	len = 0;
	while (tab[len])
		len++;
	return (len);
}

// copy adress of each element of tab, in a new_tab
// Doesnt copy the element at index if index is >= 0
char **tabstrcpy(char **tab, int index)
{
	char **new_tab;
	int		len;
	int		i;
	int		offset;

	len = tablen(tab);
	if (index >= 0)
		len--;
	new_tab = malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	i = 0;
	offset = 0;
	while (tab[i + offset])
	{
		if (i == index)
			offset++;
		new_tab[i] = tab[i + offset];
		if (tab[i + offset])
			i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static char	**unset_env(char *name, t_data *data)
{
	int		env_index;
	char	**new_env;

	env_index = exist(data->envp, name);
	if (env_index < 0)
		return (data->envp);
	new_env = tabstrcpy(data->envp, env_index);
	if (!new_env)
		return (data->envp);
	free(data->envp[env_index]);
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
