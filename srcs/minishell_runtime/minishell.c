/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/02/10 17:25:09 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get user prompt
char	*listen_to_user(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (!input)
		return (NULL);
	add_history(input);
	return (input);
}

void	init_shell(t_data *data)
{
	rl_catch_signals = 0; // Disable readline's signal handling
	g_signal_caught = 0;
	data->tree = NULL;
	data->token_list = NULL;
	data->paths = NULL;
	data->user_input = NULL;
}

int	run_shell(t_data *data)
{
	t_token				*cpy;
	static char			*tmp;

	while (1)
	{
		init_shell(data);
		tmp = catch_expand(data, "PWD");
		tmp = ft_strjoin("msh:>", tmp);
		data->prompt = ft_strjoin(tmp, ">$");
		free(tmp);
		data->user_input = listen_to_user(data->prompt);
		if (!data->user_input)
		{
			free_tabstr(data->envp);
			free_minishell(data);
			rl_clear_history();
			data->status += g_signal_caught;
			exit(data->status);
		}
		else if (data->user_input[0] == '\0')
		{
			free(data->user_input);
			free(data->prompt);
			continue ;
		}
		if (!tokenize(data))
			free_minishell(data);
		else
		{
			cpy = data->token_list;
			if (data->flag)
			{				
				printf("\n\n----------- List of tokens is :\n");
				print_list(data->token_list);
			}
			data->tree = build_tree(&cpy, CMD);
			if (data->flag)
			{
				printf("\n\n----------- Binary tree :  ----\n");
				print_tree(data->tree, 0); // print the tree for debug
			}
			execute_tree(data);
			free_minishell(data);
		}
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_data				data;

	data.flag = 0;
	data.status = 0;
	(void)argv;
	if (ac > 1)
		data.flag = 1;
	register_signals();
	data.envp = tab_dup(envp);
	init_shell(&data);
	run_shell(&data);
	free_minishell(&data);
	return (g_signal_caught);
}
