/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:35:45 by npolack           #+#    #+#             */
/*   Updated: 2024/12/12 19:41:57 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	make_child(int fd_input, int fd_output, char **args, char **env)
{
	dup2(fd_input, 0);
	dup2(fd_output, 1);
	if (execve(args[0], args, env) == -1)
	{
		ft_putendl_fd("ERROR", 2);
		exit(0);
	}
	return (-1);
}

int	main(int ac, char** av, char **env)
{
	char	**args;
	char	*cmd;
	int		fd_out;
	int		fd_in;
	char	**paths;
	pid_t		pid;
	int		pipefd[2];
	int		nb_of_cmd;
	int		i;

	paths = get_paths(env);
	fd_in = open(av[1], O_RDONLY, 0777);
	fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	nb_of_cmd = ac - 3;
	i = 1;
	if (nb_of_cmd == 1)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		close(fd_in);
		close(fd_out);
		cmd = get_full_path(paths, av[i + 1]);
		args = build_args(av[i + 1], cmd);
		if (!execve(cmd, args, env))
		{
			ft_putendl_fd("ERROR", 2);
			exit(0);
		}
	}
	else 	
	{
		int fd_tmp;

			i = 1;
			while (i <= nb_of_cmd)
			{
				pipe(pipefd);
				pid = fork();
				if (!pid)
				{
					cmd = get_full_path(paths, av[i + 1]);
					args = build_args(av[i + 1], cmd);
					if (i == 1)
					{
						make_child(fd_in, pipefd[1], args, env);


						close(fd_in);
						close(fd_out);
						close(pipefd[1]);
						close(pipefd[0]);
					}
					else if (i == nb_of_cmd)
					{
						make_child(fd_tmp, fd_out, args, env);
						//dup2(fd_out, 1);
					//	dup2(fd_tmp, 0);

						close(fd_in);
						close(fd_out);
						close(fd_tmp);
						close(pipefd[0]);
						close(pipefd[1]);
					}
					else 
					{
						make_child(fd_tmp, pipefd[1], args, env);
						/*dup2(fd_tmp, 0);
						dup2(pipefd[1], 1);*/

						close(fd_in);
						close(fd_out);
						close(fd_tmp);
						close(pipefd[0]);
						close(pipefd[1]);
					}
	
				}
				else
				{
					//close(fd_tmp);
					fd_tmp = dup(pipefd[0]);
					close(pipefd[1]);
					close(pipefd[0]);
					while (waitpid(-1, NULL, WUNTRACED) != -1)
						;
				}
				i++;
			}
			free_all(paths);
			close(fd_tmp);
	}
    //close(pipefd[0]);
    //close(pipefd[1]);
	return (0);
}


