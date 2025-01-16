/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/17 00:40:12 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get user prompt
char *listen_to_user(char *user_cmd)
{
	char	*prompt;
	prompt = readline(user_cmd);
	return (prompt);
}

// print **arguments for DEBUG
void	args_print(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
}

int	main(int ac, char **argv, char **envp)
{
	char		*user_input;
	t_bintree	*tree;
	t_token		*list;
	char		*prompt;

	(void)argv;
	(void)ac;
	(void)envp;

	prompt = "MINISHELL/is/listening/to/you >";
	user_input = listen_to_user(prompt); // get the user prompt into a str
	list = tokenize(user_input); // make the token (ONLY with '|')
	tree = build_tree(list); // make the tree from t_token *list
	//execute_tree(tree, envp); // execute tree (not ready)
	print_tree(tree); // print the tree for debug
	free(user_input);
	// free t_token
	// free tree
}
