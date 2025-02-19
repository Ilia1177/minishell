/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:50:24 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 17:08:39 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"

t_cmd	*make_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->rdir = NULL;
	return (cmd);
}

t_type	get_type(char *str)
{
	t_type	type;

	if (!ft_strcmp(str, "&"))
		return (-1);
	else if (!ft_strcmp(str, "|"))
		type = PIPE;
	else if (!ft_strcmp(str, "||"))
		type = OPERATOR;
	else if (!ft_strcmp(str, "&&"))
		type = OPERATOR;
	else if (!ft_strcmp(str, "("))
		type = OPERATOR;
	else if (!ft_strcmp(str, ")"))
		type = OPERATOR;
	else
		type = CMD;
	return (type);
}

// make a token 
t_token	*make_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->input = ft_strdup(str);
	token->type = get_type(str);
	if (token->type == CMD)
		token->cmd = make_cmd();
	else
		token->cmd = NULL;
	token->next = NULL;
	return (token);
}
