/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:21:45 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/24 09:43:34 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstiter_token(t_token *lst, void (*f)(t_token *))
{
	t_token	*iterator;

	if (!lst || !f)
		return ;
	iterator = lst;
	while (iterator)
	{
		(*f)(iterator);
		iterator = iterator->next;
	}
}

void	split_args(t_token *token)
{
	t_cmd	*cmd;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return ;
	cmd->args = NULL;
	if (token->type == CMD)
	{
		cmd->args = ft_split(token->input, ' ');
		token->cmd = cmd;
		printf("%s", token->cmd->args[0]);
	}
}

void	type_token(t_token *token)
{
	if (!ft_strcmp(token->input, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->input, "||"))
		token->type = OPERATOR;
	else if (!ft_strcmp(token->input, "&&"))
		token->type = OPERATOR;
	else if (!ft_strcmp(token->input, "$"))
		token->type = EXPAND;
	else if (!ft_strcmp(token->input, "("))
		token->type = OPERATOR;
	else if (!ft_strcmp(token->input, ")"))
		token->type = OPERATOR;
	else
		token->type = CMD;
}
