/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:27:25 by npolack           #+#    #+#             */
/*   Updated: 2025/02/19 18:01:06 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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
	int		len;
	int		error;
	char	*name;

	len = 0;
	error = 0;
	*buff = NULL;
	if (!ft_isalpha(*str))
		error = 1;
	while (str[len])
	{
		if (str[len] == '+' || str[len] == '=')
			break ;
		if (isspace(str[len]) || !ft_isalnum(str[len]))
			error = 1;
		len++;
	}
	if (!str[len])
		error = -1;
	else if (str[len] == '+' && str[len + 1] != '=')
		error = 1;
	name = malloc(sizeof(char) * len + 1);
	if (!name)
		return (-1);
	ft_strlcpy(name, str, len + 1);
	*buff = name;
	return (error);
}

//	char	*catch_value(char *str)
//	{
//		char	*value;
//		int		i;
//		int		len;
//
//		if (ft_strlen(str) == ft_strnlen(str, '='))
//			return (NULL);
//		str += ft_strnlen(str, '=');
//		len = ft_strlen(++str);
//		value = malloc(sizeof(char) * len + 1);
//		if (!value)
//			return (NULL);
//		i = 0;
//		while (str[i])
//		{
//			value[i] = str[i];
//			i++;
//		}
//		value[i] = '\0';
//		return (value);
//	}

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
