/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/01/24 21:42:39 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// make a token 
t_token	*make_token(char *str, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->input = ft_strdup(str); // build **args from str
	token->type = type;
	token->cmd = NULL;
	token->next = NULL;
	return (token);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*current_token;
	t_token	*previous_token;
	char	**tokens;
	int		i;

	if (!input)
		return(NULL);
	tokens = ft_split_token(input);
	i = 0;
	head = make_token(tokens[i], CMD);
	current_token = head;
	while (tokens[++i])
	{
		previous_token = current_token;
		current_token = make_token(tokens[i], CMD);
		previous_token->next = current_token;
	}
	ft_lstiter_token(head, &type_token);
	ft_lstiter_token(head, &split_args);
	ft_lst_split_dup(&head, &ft_count_dup, "()");
	free_tabstr(tokens);
	return (head);
}
