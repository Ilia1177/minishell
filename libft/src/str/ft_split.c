/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:26:02 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/16 11:16:13 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbword(const char *s, char c)
{
	int	nb_word;
	int	i;

	i = 0;
	nb_word = 0;
	while (s[i] != '\0')
	{
		if (i == 0 && s[i] != c)
			nb_word++;
		else if (s[i] != c && s[i - 1] == c)
			nb_word++;
		i++;
	}
	return (nb_word);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != '\0' && s[strlen] != c)
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

static char const	*ft_go_word(char const *str, char c)
{
	while (*str != '\0' && *str == c)
		str++;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;
	int		nb_word;

	if (!s)
		return (NULL);
	nb_word = ft_nbword(s, c);
	str = (char **) ft_calloc(nb_word + 1, sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (*s != '\0' && i < nb_word)
	{
		s = ft_go_word(s, c);
		str[i] = (char *) ft_calloc(ft_wordlen(s, c) + 1, sizeof(char));
		if (!str[i])
		{
			ft_free_bugsplit(str, i - 1);
			return (NULL);
		}
		ft_strlcpy(str[i], s, ft_wordlen(s, c) + 1);
		s += ft_wordlen(s, c);
		i++;
	}
	return (str);
}
