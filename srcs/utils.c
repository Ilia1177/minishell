/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:03:36 by npolack           #+#    #+#             */
/*   Updated: 2024/12/12 15:11:10 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_paths(char **env)
{
	char **paths;
	int		i;

	paths = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			env[i] += 5;
			paths = ft_split(env[i], ':');
			env[i] -= 5;
			return (paths);
		}
		i++;
	}

	return (paths);
}

char *get_full_path(char **paths, char *str)
{
	int	i;
	char *full_path;
	char *cmd;
	char *tmp;

	tmp = malloc(sizeof(char) * (ft_strnlen(str, ' ') + 1));
	i = -1;
	while (++i < ft_strnlen(str, ' '))
		tmp[i] = str[i];
	tmp[i] = '\0';
	cmd = ft_strjoin("/", tmp);
	free(tmp);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (!access(full_path, X_OK))
		{
			free(cmd);
			return (full_path);	
		}
		free(full_path);
		i++;
	}
	free(cmd);
	return (NULL);
}

char	**build_args(char *av, char *cmd)
{
	char **args;
	char *string;
	char *tmp;

	while(*av && *av != ' ')
		av++;
	string = ft_strjoin(cmd, " ");
	tmp = string;
	string = ft_strjoin(tmp, av);
	args = ft_split(string, ' ');
	free(tmp);
	return (args);
}

int free_all(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}

void wait_all_child(int child_nb) 
{
	int status;
	int n = 0;
	while (n < child_nb)
	{
		wait(&status);
		n++;
	}
}
void	printargs(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putendl_fd(args[i], 2);
		i++;
	}
}
