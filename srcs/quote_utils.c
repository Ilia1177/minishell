/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:40:34 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/04 17:02:43 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quote(char *str, char quote)
{
	int	len;

	if (!str || (quote != '\'' && quote != '"'))
		return (0);
	len = 1;
	while (str[len] && str[len] != quote)
		len++;
	if (str[len] == quote)
		len++;
	return (len);
}

char	find_next_quote(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (*str);
		str++;
	}
	return (0);
}

char	*get_quotedword(char **str)
{
	char	*word;

	word = ft_substr(*str, 1, ft_strnlen(*str + 1, **str));
	*str += ft_strnlen(*str + 1, **str) + 2;
	return (word);
}

char	*get_cleanword(char **str)
{
	char	quote;
	char	*word;

	quote = find_next_quote(*str);
	word = ft_substr(*str, 0, ft_strnlen(*str, quote));
	*str += ft_strnlen(*str, quote);
	return (word);
}

char	*remove_quote(char *str)
{
	char	*tmp;
	char	*arg;
	char	*word;

	arg = NULL;
	word = 0;
	while (*str)
	{
		if (ft_isquote(*str))
			word = get_quotedword(&str);
		else
			word = get_cleanword(&str);
		if (!arg)
			arg = word;
		else
		{
			tmp = arg;
			arg = ft_strjoin(arg, word);
			free(tmp);
			free(word);
		}
	}
	return (arg);
}
