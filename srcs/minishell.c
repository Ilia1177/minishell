/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 16:19:01 by npolack           #+#    #+#             */
/*   Updated: 2025/01/20 14:19:22 by npolack          ###   ########.fr       */
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
	//char		*prompt;

	(void)argv;
	(void)ac;
	(void)envp;
	user_input = NULL;
	//prompt = "MINISHELL/is/listening/to/you >";
	//user_input = listen_to_user(prompt); // get the user prompt into a str
	

	// echo "world" >> test | cat -n test | < test grep world | wc -l && cat test
//	list = make_token("C1", CMD);		 
//	list->next = make_token("||", OPERATOR);		 
//	list->next->next = make_token("C2", CMD);		 
//	list->next->next->next = make_token("|", PIPE);		 
//	list->next->next->next->next = make_token("C3", CMD);		 
//	list->next->next->next->next->next = make_token("|", PIPE);		 
//	list->next->next->next->next->next->next = make_token("C4", CMD);		 
//	list->next->next->next->next->next->next->next = make_token("&&", OPERATOR);
//	list->next->next->next->next->next->next->next->next = make_token("C5", CMD);
//	list->next->next->next->next->next->next->next->next->next = make_token("||", OPERATOR);
//	list->next->next->next->next->next->next->next->next->next->next = make_token("C6", CMD);

	list = make_token("C1", CMD);		 
	list->next = make_token("|a", PIPE);		 
	list->next->next = make_token("(", OPERATOR); 
	list->next->next->next = make_token("C", CMD); 
	list->next->next->next->next = make_token("||", OPERATOR);		 
	list->next->next->next->next->next = make_token("C", CMD);		 
	list->next->next->next->next->next->next = make_token(")", OPERATOR);		 
	list->next->next->next->next->next->next->next = make_token("|", PIPE);
	list->next->next->next->next->next->next->next->next = make_token("(", OPERATOR);
	list->next->next->next->next->next->next->next->next->next = make_token("C5", CMD);
	list->next->next->next->next->next->next->next->next->next->next = make_token("||", OPERATOR);
	list->next->next->next->next->next->next->next->next->next->next->next = make_token("C6", CMD);
	list->next->next->next->next->next->next->next->next->next->next->next->next = make_token(")", OPERATOR);
	list->next->next->next->next->next->next->next->next->next->next->next->next->next = make_token("&&", OPERATOR);
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next = make_token("C", CMD);
	list->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next = NULL;

	print_list(list);
	//list = tokenize(user_input); // make the token (ONLY with '|')
	tree = build_tree(&list, CMD); // make the tree from t_token *list
	print_tree(tree); // print the tree for debug
	free(user_input);
	free_tree(tree);
}
