/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:27:25 by npolack           #+#    #+#             */
/*   Updated: 2025/02/12 14:55:42 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	print_env(t_bintree *node, char **envp, char *format)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
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
