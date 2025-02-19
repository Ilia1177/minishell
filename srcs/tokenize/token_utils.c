/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:02 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 18:38:36 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "parsing.h"

int	cmd_len(char *str)
{
	int	len;

	len = 0;
	while (!ft_issep(str[len]) && str[len])
	{
		if (ft_isquote(str[len]))
			len += skip_quote((char *)(str + len), str[len]);
		else
			len++;
	}
	return (len);
}

int	sep_len(char *str)
{
	int		len;
	char	tmp_sep;

	len = 0;
	if (str[len] == ')' || str[len] == '(')
	{
		len++;
		while (isspace(str[len]))
			len++;
		return (len);
	}
	tmp_sep = str[len];
	while (ft_issep(str[len]) && str[len] == tmp_sep && len < 2)
		len++;
	while (isspace(str[len]) && len > 0)
		len++;
	return (len);
}
