/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:51:50 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/10 18:57:48 by npolack          ###   ########.fr       */
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

int	rdir_syntax(t_token *curr)
{
	int		error;
	int		i;
	char	*str;
	char	c;

	error = 0;
	str = curr->input;
	c = 0;
	while(*str)
	{

		if (*str == '>' || *str == '<')
		{
			i = 0;
			c = *str;
			while (str[i] == c)
				i++;
			if (i > 2)
				return (2);
			while (isspace(str[i]))
				i++;
			if (ft_isquote(str[i]))
				i += skip_quote(str + i, str[i]);
			else if (!ft_isprint(str[i]))
				return (2);
			else
			{
				while (isprint(str[i]) && !ft_isquote(str[i]))
					i++;
			}
			str += i;
		}
		else if (ft_isquote(*str))
			str += skip_quote(str, *str);
		else
			str++;
	}
	return (error);
}

int	cmd_syntax(t_token *prev, t_token *curr)
{
	int	error;

	error = 0;
	if (prev)
	{
		if (prev->type == CMD)
			return (1);
		if (!ft_strcmp(prev->input, ")"))
		{
			ft_printf(2, "Use parenthesis for priority ONLY\n");
			return (1);
		}
	}
	error = rdir_syntax(curr);
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
		ft_printf(2, SYNTERR);
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
		ft_printf(2, SYNTERR);
	return (close);
}

int	open_parenthesis(char *str)
{
	int	open;

	open = 0;
	while (*str)
	{
		if (*str == '(')
			open += 1;
		else if (*str == ')')
			open -= 1;
		if (ft_isquote(*str))
			str += skip_quote(str, *str);
		else
			str++;	
	}
	if (open > 0)
		ft_printf(2, SYNTERR);
	if (open < 0)
		ft_printf(2, SYNTERR);
	return (open);
}
