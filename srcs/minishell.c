/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/24 12:36:45 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get user prompt
char	*listen_to_user(char *prompt)
{
	char	*input;

	input = readline(prompt);
	return (input);
}

int	main(int ac, char **argv, char **envp)
{
	char		*prompt;
	t_data		data;
	t_token		*cpy;

	(void)argv;
	(void)ac;
	data.envp = envp;

	prompt = "MINISHELL/is/listening/to/you >";
	while (1)
	{
		data.user_input = listen_to_user(prompt);
		data.token_list = tokenize(data.user_input);
		if (!syntax_error(data.user_input))
		{
			cpy = data.token_list;
			printf("----------- List of token is : -\n\n\n");
			print_list(data.token_list);

			printf("----------- DEBUG TREE ---------\n\n\n");
			data.tree = build_tree(&cpy, CMD);
			print_tree(data.tree, 0); // print the tree for debug
			printf("----------- EXECUTION ----------\n\n\n");
			execute_tree(&data); 
			free(data.user_input);
			free_tree(data.tree);
			free_tabstr(data.paths);
			free_elem(data.token_list, LST);
		}
	}
}
