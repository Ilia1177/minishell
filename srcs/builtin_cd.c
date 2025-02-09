/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:27:25 by npolack           #+#    #+#             */
/*   Updated: 2025/02/09 10:19:10 by ilia             ###   ########.fr       */
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
void	update_pwds(t_data *data)
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

void	change_dir(t_bintree *node, t_data *data)
{
	char	wd[1024];
	char	*path;

	if (!node->cmd->args[1])
		return ;
	if (!ft_strcmp(node->cmd->args[1], "-"))
		path = ft_strdup(catch_expand(data, "OLDPWD"));
	else if (!ft_strcmp(node->cmd->args[1], "--"))
		path = ft_strdup(catch_expand(data, "HOME"));
	else if (node->cmd->args[1][0] == '/')
		path = ft_strdup(node->cmd->args[1]);
	else
	{
		getcwd(wd, sizeof(wd));
		path = ft_strjoin(wd, "/");
		path = ft_strjoin(path, node->cmd->args[1]);
	}
	if (!chdir(path))
		update_pwds(data);
	else
	{
		ft_printf(2, "M!N!$H3LL: cd: include: No such file or directory\n");
		data->status = 1;
	}
	free(path);
}

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

int	catch_name(char **buff, char *str)
{
	int		i;
	int		len;
	int		error;
	char	*name;

	error = 0;
	if (!str)
		return (-1);
	len = ft_strnlen(str, '=');
	name = malloc(sizeof(char) * len + 1);
	if (!name)
		return (-1);
	if (ft_isdigit(str[0]) || str[0] == '=')
		error = 1;
	i = -1;
	while (++i < len)
	{
		if (is_space(str[i]) || !ft_isalnum(str[i]))
			error = 1;
		name[i] = str[i];
	}
	name[i] = '\0';
	*buff = name;
	return (error);
}

char	*catch_value(char *str)
{
	char	*value;
	int		i;
	int		len;

	str += ft_strnlen(str, '=');
	len = ft_strlen(++str);
	value = malloc(sizeof(char) * len + 1);
	if (!value)
		return (NULL);
	i = 0;
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
		return (tmp);
	free(tmp);
	if (!value)
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
		if (error == 1)
			ft_printf(2, "msh: export : `%s\"%s\n", name, WARNING);
		free(name);
	}
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
	while (node->cmd->args[j])
	{
		if (update_envp(data, node->cmd->args[j]))
			status = 1;
		j++;
	}
	data->status = status;
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

char	**unset_env(char *name, char **old_envp)
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
			i++;
		new_env[++j] = old_envp[i];
	}
	new_env[j] = NULL;
	free(old_envp);
	return (new_env);
}

void	unset(t_bintree *node, t_data *data)
{
	int	i;

	i = 1;
	if (!node->cmd->args[i])
		return ;
	while (node->cmd->args[i])
	{
		data->envp = unset_env(node->cmd->args[1], data->envp);
		i++;
	}
}
