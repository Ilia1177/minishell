/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:20:15 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/10 16:57:04 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* allows you to include what is between quote as a string
 * one bloc between same quote
 * i in is pos of first quote
 * i out is pos of char the end quote
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
*/

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

int	ft_nbword(const char *s)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		if (ft_issep(s[i]))
			i += sep_len((char *)s + i);
		else if (!ft_issep(s[i]))
			i += cmd_len((char *)s + i);
		nb_word++;
	}
	return (nb_word);
}

static size_t	ft_wordlen(const char *s)
{
	int		len;

	len = 0;
	if (ft_issep(s[len]))
		len += sep_len((char *)s);
	else
		len += cmd_len((char *)s);
	return (len);
}


char	*build_input(const char *s)
{
	char	*tmp;
	char	*str;
	int		all_space;
	int		i;

	tmp = ft_substr(s, 0, ft_wordlen(s));
	if (!tmp)
		return (NULL);
	all_space = 1;
	i = -1;
	while (tmp[++i])
		if (!isspace(tmp[i]))
			all_space = 0;
	if (all_space)
	{
		free(tmp);
		return (NULL);
	}
	str = ft_strtrim(tmp, "\r\f\v\n\t ");
	free(tmp);
	return (str);
}

/* this function split the input of the user
 * in token which could be ;
 * --a command
 * --a operator
 * --a paremthesis*/

// is the tab null terminated ???
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
	i = -1;
	while (*s && ++i < nb_word)
	{
		str[i] = build_input(s);
		if (!str[i])
		{
			ft_free_bugsplit(str, i - 1);
			return (NULL);
		}
		s += ft_wordlen(s);
	}
	return (str);
}
