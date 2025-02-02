/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:27:25 by npolack           #+#    #+#             */
/*   Updated: 2025/01/30 21:07:50 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	change_pwd(t_data *data, char *path) */
/* { */
/* 	char *old_path; */
/* 	char	*new_path; */	
/* 	(void)data; */

/* 	old_path = getenv("PWD"); */
/* 	printf("path = %s\n", old_path); */
/* 	new_path = ft_strjoin("PATH=", path); */
/* } */

/* int	change_dir(t_cmd *cmd, t_data *data) */
/* { */
/* 	if (!chdir(path)) */
/* 		return (-1); */
/* 	change_pwd(data, path); */
/* 	return (0); */
/* } */

int	echo(t_bintree *node, t_data *data)
{
	int		i;

	(void)data;
	if (!node->cmd->args)
		return (0);
	i = 1;
	if (node->cmd->args[1] && !ft_strcmp(node->cmd->args[1], "-n"))
		i = 2;
	while (node->cmd->args[i])
	{
		ft_printf(node->stdfd[OUT], "%s", node->cmd->args[i]);
		if (node->cmd->args[i + 1])
			ft_printf(node->stdfd[OUT], " ");
		i++;
	}
	if (node->cmd->args[1] && ft_strcmp(node->cmd->args[1], "-n"))
		ft_printf(node->stdfd[OUT], "\n");
	else if (!node->cmd->args[1])
		ft_printf(node->stdfd[OUT], "\n");
	data->status = 0;
	return (0);
}

int	print_working_dir(t_bintree *node, t_data *data)
{
	char		wd[1024];

	(void)data;
	if (getcwd(wd, sizeof(wd)))
		ft_printf(node->stdfd[OUT], "%s\n", wd);
	else
	{
		data->status = 256;
		return (256);
	}
	data->status = 0;
	return (0);
}

char	*catch_name(char *str)
{
	int		i;
	int		len;
	char	*name;
	char	*warning;

	warning = ": not a valid identifier";
	if (!str)
		return (NULL);
	len = ft_strnlen(str, '=');
	if (len == (int)ft_strlen(str))
		return (NULL);
	name = malloc(sizeof(char) * len + 1);
	if (!name)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (is_space(str[i]) || !ft_isalnum(str[i]))
		{
			ft_printf(2, "minishell : export : `%s\"%s\n", str, warning);
			free(name);
			return (NULL);
		}
		name[i] = str[i];
	}
	name[i] = '\0';
	return (name);
}

char	*catch_value(char *str)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	str += ft_strnlen(str, '=');
	len = ft_strlen(++str);
	value = malloc(sizeof(char) * len + 1);
	while (str[i])
	{
		value[i] = str[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*new_entry(char *name, char *value)
{
	char	*tmp;
	char	*line;

	tmp = name;
	name = ft_strjoin(name, "=");
	if (!name)
		return (NULL);
	free(tmp);
	if (!value)
		line = name;
	else
	{
		line = ft_strjoin(name, value);
		if (!line)
			return (NULL);
		free(name);
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

int	exist(char **envp, char *name)
{
	int	i;

	if (!envp || !name)
		return (-1);
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], name, ft_strlen(name)))
			return (i);
	return (-1);
}
	
int	update_envp(t_data *data, char *str)
{
	char	*tmp;
	char	*name;
	char	*value;
	int		at_index;

	name = catch_name(str);
	if (name)
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
		data->status = 1;
	return (0);
}

int	export(t_bintree *node, t_data *data)
{
	int		j;

	j = 1;
	if (!node->cmd->args[j])
		print_env(node, data->envp, "declare -x ");
	while (node->cmd->args[j])
	{
		update_envp(data, node->cmd->args[j]);
		j++;
	}
	return (0);
}

int	print_env(t_bintree *node, char **envp, char *format)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	else
	{
		while (envp[i])
		{
			ft_printf(node->stdfd[OUT], "%s%s\n", format, envp[i]);
			i++;
		}
	}
	return (0);
}
