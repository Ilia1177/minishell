/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 19:33:49 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get user prompt
char	*listen_to_user(char *user_cmd)
{
	char	*prompt;

	prompt = readline(user_cmd);
	return (prompt);
}

int	main(int ac, char **argv, char **envp)
{
	char		*prompt;
	t_data		data;

	(void)argv;
	(void)ac;
	data.envp = envp;

	printf("%d\n", CMD);
	prompt = "MINISHELL/is/listening/to/you >";
	data.user_input = listen_to_user(prompt);
	//data.list = tokenize(data.user_input);
	data.list = make_token("C");
	data.list->type = CMD;
	data.list->next = make_token("|");
	data.list->next->type = PIPE;
	data.list->next->next = make_token("C");
	data.list->next->next->type = CMD;
	print_list(data.list);
	data.tree = build_tree(&data.list, CMD);
	//execute_tree(tree, envp); // execute tree (not ready)
	print_tree(data.tree); // print the tree for debug
	free(data.user_input);
	free_tree(data.tree);
	// free t_token
	// free tree
}
