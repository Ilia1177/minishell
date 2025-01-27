/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:21:45 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/27 19:28:52 by jhervoch         ###   ########.fr       */
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

int arg_len(char *str)
{
	int len;

	len = 0;
	while (str[len] && !is_space(str[len]))
	{
		if (ft_isquote(str[len]))
			ft_skip_quote(&str[len], &len);
		if (str[len])
			len++;
	}
	return (len);
}

int ft_nb_args(const char *s)
{
	int	nb_args;
	int	i;

	nb_args = 0;
	i = 0;

	while (s[i])
	{
		if (i == 0 && !is_space(s[i]))
			nb_args++;
		else if (!is_space(s[i]) && is_space(s[i - 1]))
			nb_args++;
		while (ft_isquote(s[i]))
			ft_skip_quote(&s[i], &i);
		if (s[i])
			i++;
	}
	return (nb_args);
}

void	split_args(t_token *token)
{
	t_cmd	*cmd;
	int		nb_args;
	int		i;
	char *input;


	if (token->type == CMD)
	{
		input = token->input;
		i = 0;
		cmd = malloc (sizeof(t_cmd));
		if (!cmd)
			return ;
		nb_args = ft_nb_args(token->input);
		cmd->args = ft_calloc(nb_args + 1, sizeof(char *));
		if (!cmd->args)
			return ;
		//cmd->args = NULL;
		printf("args: %d", nb_args);
		while (*input && i < nb_args)
		{
			while (*input && is_space(*input) && !ft_isquote(*input))
				input++;
			cmd->args[i] = ft_calloc(arg_len(input)+1, sizeof(char));
			if (!cmd->args[i])
			{
				ft_free_bugsplit(cmd->args, i -1);
				return ; 
			}
			ft_strlcpy(cmd->args[i], input, arg_len(input)+1);
			input += arg_len(input);
			i++;
		}
		/* cmd->args = ft_split(token->input, ' '); */
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
