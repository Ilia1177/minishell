/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:20:15 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/20 15:17:21 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_issep(char c)
{
	const char *sep = "|&";

	while (*sep)
	{
		if (*sep == c)
			return (1);
		sep++;
	}
	return (0);
}

int	ft_nbword(const char *s)
{
	int	nb_word;
	int	i;

	i = 0;
	nb_word = 0;
	while (s[i] != '\0')
	{
		if (ft_issep(s[i]))
			nb_word++;
		while (s[i] && ft_issep(s[i]))
				++i;
		if (s[i] && !ft_issep(s[i]))
			nb_word++;
		while (s[i] && !ft_issep(s[i]))
			++i;
	}
	return (nb_word);
}

static size_t	ft_wordlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	if (ft_issep(s[strlen]))
		while (s[strlen] && ft_issep(s[strlen]))
			strlen++;
	else
		while (s[strlen] && !ft_issep(s[strlen]))
			strlen++;
	return (strlen);
}

static void	ft_free_bugsplit(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

char	**ft_split_token(char const *s)
{
	int		i;
	char	**str;
	int		nb_word;

	if (!s)
		return (NULL);
	nb_word = ft_nbword(s);
	str = (char **) ft_calloc(nb_word + 1, sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (*s != '\0' && i < nb_word)
	{
		str[i] = (char *) ft_calloc(ft_wordlen(s) + 1, sizeof(char));
		if (!str[i])
		{
			ft_free_bugsplit(str, i - 1);
			return (NULL);
		}
		ft_strlcpy(str[i], s, ft_wordlen(s) + 1);
		s += ft_wordlen(s);
		i++;
	}
	return (str);
}
