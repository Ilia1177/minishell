/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/17 16:55:30 by npolack          ###   ########.fr       */
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
	char		*user_input;
	t_bintree	*tree;
	t_token		*list;
	char		*prompt;

	(void)argv;
	(void)ac;
	(void)envp;
	user_input = NULL;
	prompt = "MINISHELL/is/listening/to/you >";
	//user_input = listen_to_user(prompt); // get the user prompt into a str
	

	// echo "world" >> test | cat -n test | < test grep world | wc -l && cat test
	list = make_token("echo world", CMD);		 
	list->next = make_token(">> test", OUT_ARDIR);		 
	list->next->next = make_token("|", PIPE);		 
	list->next->next->next = make_token("cat -n test", CMD);		 
	list->next->next->next->next = make_token("< test", IN_RDIR);		 
	list->next->next->next->next->next = make_token("grep world", CMD);		 
	list->next->next->next->next->next->next = make_token("|", PIPE);		 
	list->next->next->next->next->next->next->next = make_token("wc -l", CMD);
	list->next->next->next->next->next->next->next->next = make_token("&&", OPERATOR);
	list->next->next->next->next->next->next->next->next->next = make_token("cat test", CMD);

	//list = tokenize(user_input); // make the token (ONLY with '|')
	tree = build_tree(list); // make the tree from t_token *list
	//execute_tree(tree, envp); // execute tree (not ready)
	print_tree(tree); // print the tree for debug
	free(user_input);
	// free t_token
	free_tree(tree);
}
