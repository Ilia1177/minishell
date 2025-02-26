/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:21:43 by npolack           #+#    #+#             */
/*   Updated: 2025/02/26 18:19:46 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "tokenize.h"
#include "parsing.h"

static t_token	*add_back_tokenlist(t_token **head, t_token **lst, char *tokens)
{
	t_token	*curr_token;
	t_token	*prev_token;

	prev_token = *lst;
	curr_token = make_token(tokens);
	if (prev_token)
		prev_token->next = curr_token;
	if (!*head)
		*head = curr_token;
	if (catch_syntax_error(prev_token, curr_token))
	{
		ft_lstclear_token(head, &free);
		return (NULL);
	}
	return (curr_token);
}

static t_token	*build_tokenlist(char **tokens)
{
	int		i;
	t_token	*head;
	t_token	*curr_token;	

	i = 0;
	head = NULL;
	curr_token = NULL;
	curr_token = add_back_tokenlist(&head, &curr_token, tokens[i]);
	while (curr_token && tokens[++i])
	{
		curr_token = add_back_tokenlist(&head, &curr_token, tokens[i]);
		if (!curr_token)
			return (NULL);
	}
	if (curr_token && curr_token->type != CMD)
	{
		ft_lstclear_token(&head, &free);
		ft_printf(2, SYNTERR);
		return (NULL);
	}
	return (head);
}

/****************************************************
 * Tokenize the user input
 * make linked list of token
 * with several function that iter of this list
 * like filter
 * *************************************************/
int	tokenize(t_data *data)
{
	char	**tokens;

	if (!data->user_input)
		return (0);
	if (!check_closing_quote(data->user_input)
		|| open_parenthesis(data->user_input))
		return (0);
	tokens = ft_split_token(data->user_input);
	if (!tokens)
		return (0);
	data->token_list = build_tokenlist(tokens);
	free_tabstr(tokens);
	if (!data->token_list)
	{
		data->status = 2;
		return (0);
	}
	ft_lstiter_token(data, &get_redir);
	ft_lstiter_token(data, &get_expand);
	ft_lstiter_token(data, &split_args);
	ft_lstiter_token(data, &wildcards);
	ft_lstiter_token(data, &unquote_rdir);
	ft_lstiter_token(data, &unquote);
	return (1);
}
