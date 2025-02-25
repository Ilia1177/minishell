/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:37:01 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 18:49:28 by jhervoch         ###   ########.fr       */
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

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
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

int	is_all_space(char *str)
{
	int	i;
	int	is_all_space;

	is_all_space = 1;
	i = 0;
	while (str[i])
	{
		if (!isspace(str[i]))
			is_all_space = 0;
		i++;
	}
	return (is_all_space);
}

int	input_has_pipe(t_bintree *tree)
{
	int		has_pipe;

	if (tree == NULL)
		return (0);
	has_pipe = 0;
	has_pipe += input_has_pipe(tree->right);
	has_pipe += input_has_pipe(tree->left);
	if (tree->type == PIPE)
		has_pipe += 1;
	return (has_pipe);
}
