/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:26:02 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/21 14:29:26 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_issep(char c)
{
	const char	*sep = "|&()";

	while (*sep)
	{
		if (*sep == c)
			return (1);
		sep++;
	}
	return (0);
}

int	ft_isquote(char c)
{
	const char	*quote = "'\"";

	while (*quote)
	{
		if (*quote == c)
			return (1);
		quote++;
	}
	return (0);
}
