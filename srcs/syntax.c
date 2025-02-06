/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:51:50 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/06 14:21:23 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parenthesis_syntax(t_token *prev, t_token *curr)
{
	int	error;

	error = 0;
	if (!prev)
	{
		if (!ft_strcmp(curr->input, "("))
			return (0);
		else
			return (1);
	}
	if (!ft_strcmp(curr->input, "("))
	{
		if (prev->type == CMD || !ft_strcmp(prev->input, ")"))
			error = 1;
	}
	else if (!ft_strcmp(curr->input, ")"))
	{
		if (!ft_strcmp(prev->input, ")"))
			error = 0;
		else if (prev->type == OPERATOR || prev->type == PIPE)
			error = 1;
	}
	return (error);
}

int	operator_syntax(t_token *prev)
{
	int	error;

	if (!prev)
		return (1);
	error = 0;
	if (!ft_strcmp(prev->input, ")"))
		error = 0;
	else if (prev->type == PIPE || prev->type == OPERATOR)
		error = 1;
	return (error);
}

int	rdir_syntax(t_token *curr, int c)
{
	char	*sym;
	int		error;
	int		i;

	error = 0;
	sym = ft_strchr(curr->input, c);
	while (sym && *sym)
	{
		i = 0;
		while (sym[i] == c)
			i++;
		if (i > 2)
			return (258);
		while (isspace(sym[i]))
			i++;
		if (!sym[i] || sym[i] == '>' || sym[i] == '<')
			return (258);
		else if (ft_isprint(sym[i]))
			error = 0;
		else
			error = 1;
		sym = ft_strchr(sym + i, c);
	}
	return (error);
}

int	cmd_syntax(t_token *prev, t_token *curr)
{
	int	error;

	error = 0;
	if (prev)
	{
		if (prev->type == CMD || !ft_strcmp(prev->input, ")"))
			return (1);
	}
	error = rdir_syntax(curr, '<');
	if (!error)
		error = rdir_syntax(curr, '>');
	return (error);
}

int	catch_syntax_error(t_token *prev, t_token *curr)
{
	int	error;

	error = 0;
	if (!curr)
		return (-1);
	else if (!prev)
	{
		if (curr->type != CMD && ft_strcmp(curr->input, "("))
			error = 1;
		else if (!ft_strcmp(curr->input, "("))
			return (0);
		else
			error = cmd_syntax(prev, curr);
	}
	else if (!ft_strcmp(curr->input, "&"))
		error = 1;
	else if (!ft_strcmp(curr->input, ")") || !ft_strcmp(curr->input, "("))
		error = parenthesis_syntax(prev, curr);
	else if (curr->type == OPERATOR || curr->type == PIPE)
		error = operator_syntax(prev);
	else if (curr->type == CMD)
		error = cmd_syntax(prev, curr);
	if (error)
		ft_printf(2, "SYNTERR (syntax err) '%s'\n", curr->input);
	return (error);
}

int	check_closing_quote(char *str)
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
	if (!close)
		ft_printf(2, "SYNTERR NEAR '\"'\n");
	return (close);
}

int	syntax_error(char *str)
{
	int	i;

	if (!check_closing_quote(str) || str[0] == '|' || str[0] == '&')
	{
		printf(SYNTERR"\n");
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_strnlen(str, str[i]);
		else if (!ft_strncmp(&str[i], "&|", 2) || !ft_strncmp(&str[i], "|&", 2)
			|| !ft_strncmp(&str[i], "|||", 3) || !ft_strncmp(&str[i], "<<<", 3)
			|| !ft_strncmp(&str[i], ">>>", 3))
		{
			printf(SYNTERR"\n");
			return (1);
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	open_parenthesis(char *str)
{
	int	open;

	open = 0;
	while (*str)
	{
		str += skip_quote(str, *str);
		if (*str == '(')
			open += 1;
		else if (*str == ')')
			open -= 1;
		str++;	
	}
	if (open > 0)
		ft_printf(2, "SYNTERR NEAR '('\n");
	if (open < 0)
		ft_printf(2, "SYNTERR NEAR ')'\n");
	return (open);
}
