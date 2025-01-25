/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/25 00:37:28 by ilia             ###   ########.fr       */
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

void	free_minishell(t_data *data)
{
	free(data->user_input);
	close_all_fd(data->tree);
	free_tree(data->tree);
	free_tabstr(data->paths);
	free_elem(data->token_list, LST);
	//rl_clear_history(); 				doesnt work, dont know why ??
}

void	init_shell(t_data *data)
{
	signal_caught = 0;
	data->tree = NULL;
	data->token_list = NULL;
	data->paths = NULL;
	data->user_input = NULL;
}

int	run_shell(t_data *data)
{
	char		*prompt;
	t_token		*cpy;

	prompt = "MINISHELL/is/listening/to/you>";
	while (1)
	{
		data->user_input = listen_to_user(prompt);
		if (listen_to_signal(data))
		{
			close(0);
			continue ;
		}			// doesnt trigger...
		if (!data->user_input || !ft_strcmp(data->user_input, ""))	// doesnt work either...
		{
			printf("ctrl-d");
			free_minishell(data);
			exit(0);
		}
		data->token_list = tokenize(data->user_input);
		//if (!syntax_error(data->user_input))
		//{
			cpy = data->token_list;
			printf("\n\n----------- List of token is : -");
			print_list(data->token_list);
			printf("\n\n----------- DEBUG TREE ---------");
			data->tree = build_tree(&cpy, CMD);
			print_tree(data->tree, 0); // print the tree for debug
			print_list(data->token_list);
			printf("\n\n----------- EXECUTION ----------");
			execute_tree(data); 
		//}
	}
}

int	main(int ac, char **argv, char **envp)
{
	t_data				data;

	(void)argv;
	if (register_signals() == -1)
	{
		perror("minishell: signals");
		exit(0);
	}
	if (ac > 1)
		printf("minishell: ???\n");
	if (!envp)
		data.envp = getenv();
	else
		data.envp = envp;
	init_shell(&data);
	run_shell(&data);
	return(signal_caught);
}
