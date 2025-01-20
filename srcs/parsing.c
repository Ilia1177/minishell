/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:21:45 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/20 18:06:38 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstiter_token(t_token *lst, void (*f)(char *))
{
	t_token	*iterator;

	if (!lst || !f)
		return ;
	iterator = lst;
	while (iterator)
	{
		(*f)(iterator->input);
		iterator = iterator->next;
	}
}


void	type_token(t_token *token)
{
	if (ft_strcmp(token->input, "|"))
		token->type = PIPE;
	else if (ft_strcmp(token->input, "||"))
		token->type = OPERATOR;
	else if (ft_strcmp(token->input, "&&"))
		token->type = OPERATOR;
	else if (ft_strcmp(token->input, "$"))
		token->type = EXPAND;
	else
		token->type = CMD;
}

