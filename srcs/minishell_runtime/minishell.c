/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/02/19 19:03:39 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"
#include "tokenize.h"

void	update_pwd_in_envp(t_data *data)
{
	char	wd[1024];
	char	*entry;

	if (getcwd(wd, 1024))
	{
		entry = ft_strjoin("PWD=", wd);
		update_envp(data, entry);
		free(entry);
	}
}

void	init_shell(t_data *data)
{
	g_signal_caught = 0;
	data->tree = NULL;
	data->token_list = NULL;
	data->paths = NULL;
	data->user_input = NULL;
}

int	run_shell(t_data *data)
{
	t_token	*cpy;

	data->prompt = "msh-4.2$";
	update_pwd_in_envp(data);
	while (1)
	{
		init_shell(data);
		if (!get_user_input(data))
			continue ;
		if (tokenize(data))
		{
			cpy = data->token_list;
			print_list(data->token_list, data);
			data->tree = build_tree(&cpy, CMD);
			print_tree(data->tree, 0, 0, data); // print the tree for debug
			data->status = execute_tree(data);
		}
		free_minishell(data, -1);
	}
	return (data->status);
}

int	main(int ac, char **argv, char **envp)
{
	t_data				data;

	data.flag = 0;
	data.status = 0;
	(void)argv;
	if (ac > 1 && !ft_strcmp("-d", argv[1]))
		data.flag = 1;
	else if (ac > 1)
	{
		ft_printf(2, "invalid options\n");
		return (2);
	}
	register_signals();
	data.envp = tab_dup(envp);
	run_shell(&data);
	free_minishell(&data, data.status);
	return (data.status);
}
