/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:51:50 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/05 11:05:29 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parenthesis_syntax(t_token *prev, t_token *curr)
{
	int	error;

	error = 0;
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

int	catch_syntax_error(t_token *prev, t_token *curr)
{
	int	error;

	if (!prev || !curr)
		return (-1);
	error = 0;
	if (!ft_strcmp(curr->input, "&"))
		error = 1;
	else if (!ft_strcmp(curr->input, ")") || !ft_strcmp(curr->input, "("))
		error = parenthesis_syntax(prev, curr);
	else if (curr->type == OPERATOR || curr->type == PIPE)
	{
		if (!ft_strcmp(prev->input, ")"))
			error = 0;
		else if (prev->type == PIPE || prev->type == OPERATOR)
			error = 1;
	}
	else if (curr->type == CMD)
	{
		if (prev->type == CMD || !ft_strcmp(prev->input, ")"))
			error = 1;
	}
	if (error)
		ft_printf(2, SYNTERR" %s\n", curr->input);
	return (error);
}

static int	check_closing_quote(char *str)
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
