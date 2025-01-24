/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/24 11:02:41 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get user prompt
char	*listen_to_user(char *prompt)
{
	char	*input;

	input = readline(prompt);
	add_history(input);
	return (input);
}

int	quit(t_data *data)
{
	(void)data;
	//rl_clear_line();
	exit(0);
}

int	main(int ac, char **argv, char **envp)
{
	char		*prompt;
	t_data		data;
	t_token		*cpy;

	(void)argv;
	(void)ac;
	data.envp = envp;

	prompt = "MINISHELL/is/listening/to/you>";
	while (1)
	{
		data.user_input = listen_to_user(prompt);
		if (!data.user_input)
			quit(&data);
		data.token_list = tokenize(data.user_input);
		cpy = data.token_list;
		printf("----------- List of token is : -\n");
		print_list(data.token_list);
		printf("----------- DEBUG TREE ---------\n");
		data.tree = build_tree(&cpy, CMD);
		print_tree(data.tree, 0); // print the tree for debug
		print_list(data.token_list);
		printf("----------- EXECUTION ----------\n");
		execute_tree(&data); 
		free(data.user_input);
		free_tree(data.tree);
		free_elem(data.token_list, LST);
		free_tabstr(data.paths);
	}
}


