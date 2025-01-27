/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:20:15 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/27 16:03:01 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* allows you to take into account what is between quote
 * one bloc between same quote */
void	ft_skip_quote(const char *s, int *index)
{
	int		i;
	char	quote;

	i = 0;
	quote = s[i];
	++i;
	*index += 1;
	while (s[i] && s[i] != quote)
	{
		++i;
		*index += 1;
	}
	if (s[i] && s[i] == quote)
		*index += 1;
}

/* count nb of word. A word could be a command and a operator
 * the tmp var allow to check if the separator does not change*/
int	ft_nbword(const char *s)
{
	int		nb_word;
	int		i;
	char	tmp_sep;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		tmp_sep = s[i];
		if (ft_isquote(s[i]))
			ft_skip_quote(&s[i], &i);
		if (ft_issep(s[i]))
			nb_word++;
		while (s[i] && ft_issep(s[i]) && s[i] == tmp_sep)
			++i;
		if (s[i] && !ft_issep(s[i]))
			nb_word++;
		while (s[i] && !ft_issep(s[i]))
		{
			++i;
			if (ft_isquote(s[i]))
				ft_skip_quote(&s[i], &i);
		}
	}
	return (nb_word);
}

/* calculate the size of a word
 * a word could be : 
 * ---a command with args
 * ---a group of identical operators*/
static size_t	ft_wordlen(const char *s)
{
	int		strlen;
	char	tmp_sep;

	strlen = 0;
	tmp_sep = s[0];
	if (ft_issep(s[strlen]))
		while (s[strlen] && ft_issep(s[strlen]) && s[strlen] == tmp_sep)
			strlen++;
	else
	{
		while (s[strlen] && !ft_issep(s[strlen]))
		{
			if (ft_isquote(s[strlen]) && s[++strlen])
				ft_skip_quote(&s[strlen], &strlen);
			if (s[strlen])
				strlen++;
		}
	}
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
/* this function split the input of the user
 * in token with coud be ;
 * --a command
 * --a operator
 * --a paremthesis*/
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
	while (*s && i < nb_word)
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
