/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:21:45 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/27 15:55:01 by jhervoch         ###   ########.fr       */
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

static int check_closing_quote(char *str)
{
	char	quote;
	int		close;

	close = 1;
	while (*str)
	{
		if (ft_isquote(*str))
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (!*str)
				close = 0;
		}
		if (*str)
			str++;
	}
	return (close);
}

int	ft_len_until_quote(char *str)
{
	int	strlen;

	strlen = 0;
	while (str[strlen] && !ft_isquote(str[strlen]))
		strlen++;
	return (strlen);
}

int	syntax_error(char *str)
{
	int	len;
	int	i;

	if (!check_closing_quote(str) || str[0] == '|' || str[0] == '&')
	{
		printf("minishell: syntax error near unexpected token\n");
		return (1);
	}
	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			ft_skip_quote(&str[i], &i);
		len = ft_len_until_quote(&str[i]);
		if (ft_strnstr(&str[i], "&|", len) || ft_strnstr(&str[i], "|&", len)
			|| ft_strnstr(&str[i], "|||", len))
		{
			printf("minishell: syntax error near unexpected token\n");
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}
