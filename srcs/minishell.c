/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/22 22:00:35 by ilia             ###   ########.fr       */
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

	printf("%d\n", CMD);
	while (1)
	{
		prompt = "MINISHELL/is/listening/to/you >";
		data.user_input = listen_to_user(prompt);
		data.token_list = tokenize(data.user_input);
		cpy = data.token_list;
		print_list(data.token_list);
		data.tree = build_tree(&cpy, CMD);
		//execute_tree(tree, envp); // execute tree (not ready)
		print_tree(data.tree, 0); // print the tree for debug
		print_list(data.token_list);
		free(data.user_input);
		free_tree(data.tree);
		free_elem(data.token_list, LST);
	}
}
