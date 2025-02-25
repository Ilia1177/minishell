/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:42:26 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/25 21:20:01 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

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

int	rdir_len(char *str)
{
	char	c;
	int		i;

	c = 0;
	i = 0;
	c = *str;
	while (str[i] == c)
		i++;
	return (i);
}

int	check_rdir_name(char *str, int *error, int iterator)
{
	int	i;

	i = iterator;
	if (i > 2)
		*error = 2;
	while (isspace(str[i]))
		i++;
	if (ft_ischarset(str[i], "<>#$!?"))
		*error = 2;
	if (ft_isquote(str[i]))
		i += skip_quote(str + i, str[i]);
	else if (!ft_isprint(str[i]))
		*error = 2;
	else
	{
		while (isprint(str[i]) && !ft_isquote(str[i]))
			i++;
	}
	return (i);
}
