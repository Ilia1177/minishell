/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/02/05 11:11:59 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_back_tokenlist(t_token **head, t_token **lst, char *tokens)
{
	t_token	*curr_token;
	t_token	*prev_token;

	curr_token = *lst;
	prev_token = curr_token;
	curr_token = make_token(tokens);
	prev_token->next = curr_token;
	if (!curr_token || catch_syntax_error(prev_token, curr_token))
	{
		ft_lstclear_token(head, &free);
		return (NULL);
	}
	return (curr_token);
}

t_token	*build_tokenlist(char **tokens)
{
	int		i;
	t_token	*head;
	t_token	*curr_token;

	i = 0;
	head = make_token(tokens[i]);
	if (!head)
		return (NULL);
	if (head->type != CMD && ft_strcmp(head->input, "("))
	{
		ft_printf(2, "SYNTERR '%s'\n", head->input);
		ft_lstclear_token(&head, &free);
		return (NULL);
	}
	curr_token = head;
	while (tokens[++i])
	{
		curr_token = add_back_tokenlist(&head, &curr_token, tokens[i]);
		if (curr_token == NULL)
			return (NULL);
	}
	return (head);
}

int	tokenize(t_data *data)
{
	char	**tokens;

	if (!data->user_input)
		return (0);
	tokens = ft_split_token(data->user_input);
	if (!tokens)
		return (0);
	data->token_list = build_tokenlist(tokens);
	if (!data->token_list)
	{
		free_tabstr(tokens);
		return (0);
	}
	ft_lstiter_token(data, &get_redir);
	ft_lstiter_token(data, &get_expand);
	ft_lstiter_token(data, &split_args);
	ft_lstiter_token(data, &unquote);
	return (1);
}
