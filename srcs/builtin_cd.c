/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:27:25 by npolack           #+#    #+#             */
/*   Updated: 2025/01/27 15:23:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_data *data, char *path)
{
	char *old_path;
	char	*new_path;	
	(void)data;

	old_path = getenv("PWD");
	printf("path = %s\n", old_path);
	new_path = ft_strjoin("PATH=", path);
}

int	change_dir(t_data *data, char *path)
{
	if (!chdir(path))
		return (-1);
	change_pwd(data, path);
	return (0);
}

/* int	echo(char *str, int option) */
/* { */
/* 	if (!str) */
/* 		return (0); */
/* 	if (option) */
/* 		printf("%s%%", str); */
/* 	else */
/* 		printf("%s\n", str); */
/* 	return (0); */
/* } */

/* int	pwd(void) */
/* { */
/* 	char	*path; */

/* 	path = getcwd(); */
/* 	printf("%s\n", path); */
/* 	free(path); */
/* } */

/* int	export(char *value) */
/* { */

/* } */

/* int	env(t_data *data) */
/* { */
/* 	if (!data->envp) */
/* 	print_args(data->envp); */
/* 	return (0); */
/* } */
