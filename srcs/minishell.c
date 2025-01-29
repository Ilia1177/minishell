/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/29 10:55:15 by npolack          ###   ########.fr       */
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
	signal_caught = 0;
	data->tree = NULL;
	data->token_list = NULL;
	data->paths = NULL;
	data->user_input = NULL;
}

int	run_shell(t_data *data)
{
	t_token		*cpy;
	char		wd[1024];
	char		*tmp;

	while (1)
	{
		if (getcwd(wd, sizeof(wd)))
		{
			tmp = ft_strjoin("M!N!$H3LL>", wd);
			data->prompt = ft_strjoin(tmp, ">$");
			free(tmp);
		}
		data->user_input = listen_to_user(data->prompt);
		if (!data->user_input || !ft_strcmp(data->user_input, ""))
		{
			free_tabstr(data->envp);
			free_minishell(data);
			rl_clear_history();
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		if (!syntax_error(data->user_input))
		{
			data->token_list = tokenize(data->user_input);
			cpy = data->token_list;
			if (data->flag)
			{
				printf("\n\n----------- List of tokens is :\n");
				print_list(data->token_list);
				printf("\n\n----------- DEBUG TREE --------\n");
			}
			data->tree = build_tree(&cpy, CMD);
			if (data->flag)
				print_tree(data->tree, 0); // print the tree for debug
			execute_tree(data); 
			free_minishell(data);
			rl_redisplay();         // Redisplay the prompt   
		}
		init_shell(data);
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_data				data;

	data.flag = 0;
	(void)argv;
	if (ac > 1)
		data.flag = 1;
	register_signals();
	data.envp = tab_dup(envp);
	init_shell(&data);
	//change_dir(&data, argv[1]);
	run_shell(&data);
	free_minishell(&data);
	return (signal_caught);
}
