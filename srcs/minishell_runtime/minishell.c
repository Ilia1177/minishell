/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/02/27 14:17:12 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "exec.h"
#include "tokenize.h"
#include "parsing.h"

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
	rl_catch_signals = 0;
	g_signal_caught = 0;
	data->tree = NULL;
	data->token_list = NULL;
	data->paths = NULL;
	data->user_input = NULL;
}

int	execute_shell(t_data *data)
{
	t_token	*cpy;

	if (!g_signal_caught)
	{
		register_sig_exec();
		cpy = data->token_list;
		print_list(data->token_list, data);
		data->tree = build_tree(&cpy, CMD);
		print_tree(data->tree, 0, 0, data);
		data->status = execute_tree(data);
	}
	else
	{
		data->status = 128 + g_signal_caught;
		ft_lstclear_token(&data->token_list, free);
	}
	return (0);
}

int	run_shell(t_data *data)
{
	data->prompt = "msh-4.2$";
	update_pwd_in_envp(data);
	while (1)
	{
		register_sig_prompt();
		init_shell(data);
		if (!get_user_input(data))
			continue ;
		if (g_signal_caught)
		{
			data->status = 128 + g_signal_caught;
			g_signal_caught = 0;
		}
		if (tokenize(data))
			execute_shell(data);
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
	data.envp = tab_dup(envp);
	run_shell(&data);
	free_minishell(&data, data.status);
	return (data.status);
}
