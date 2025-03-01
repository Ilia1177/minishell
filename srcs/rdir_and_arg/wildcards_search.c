/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:43:06 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 21:05:20 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"

/****************************************************
 * check if the pattern is present in the filename 
 * update the file name returns from pattern +1
 * returns 1 if the pattern found
 * *************************************************/
int	middle_search(char **file_str, char *pattern_str, int *nb_find)
{
	char	*tmp_str;

	tmp_str = ft_strnstr(*file_str, pattern_str, ft_strlen(*file_str));
	if (tmp_str)
	{
		tmp_str = ft_substr(tmp_str, 1, ft_strlen(tmp_str));
		free(*file_str);
		*file_str = ft_strdup(tmp_str);
		free(tmp_str);
		*nb_find += 1;
		return (1);
	}
	return (0);
}

/****************************************************
 * check if the file name ending by the pattern
 * after the last wildcards *
 * update the file name after substr -> after pattern
 * returns 1 if the pattern found
 * *************************************************/
int	end_search(char **file_str, char *pattern_str, int *nb_find)
{
	char	*tmp_str;

	tmp_str = ft_substr(*file_str, ft_strlen(*file_str)
			- ft_strlen(pattern_str), ft_strlen(*file_str));
	if (tmp_str && !ft_strcmp(tmp_str, pattern_str))
	{
		free(*file_str);
		*file_str = ft_strdup(tmp_str);
		free(tmp_str);
		*nb_find += 1;
		return (1);
	}
	free(tmp_str);
	return (0);
}

/****************************************************
 * check if the file name start by the pattern
 * before the first wildcards *
 * update the file name after substr -> after pattern
 * returns 1 if the pattern found
 * *************************************************/
int	begin_search(char **file_str, char *pattern_str, int *nb_find)
{
	char	*tmp_str;

	if (!ft_strncmp(*file_str, pattern_str, ft_strlen(pattern_str)))
	{
		tmp_str = ft_substr(*file_str, ft_strlen(pattern_str),
				ft_strlen(*file_str));
		free(*file_str);
		*file_str = ft_strdup(tmp_str);
		free(tmp_str);
		*nb_find += 1;
		return (1);
	}
	return (0);
}

void	remove_pattern_quote(char ***pattern_ptr)
{
	char	**pattern;
	char	*pattern_str;
	int		i;
	int		j;
	int		k;

	i = -1;
	pattern = *pattern_ptr;
	while (pattern[++i])
	{
		j = -1;
		k = -1;
		pattern_str = pattern[i];
		while (pattern[i][++j])
		{
			if (pattern[i][j] != '\'' && pattern[i][j] != '\"')
				pattern_str[++k] = pattern[i][j];
		}
		pattern_str[k] = '\0';
		pattern[i] = pattern_str;
	}
	*pattern_ptr = pattern;
}

t_list	*build_from_pattern(t_list *lad, t_list *ld, char *argument)
{
	char	**patterns;
	t_list	*mfl;

	patterns = ft_split(argument, '*');
	if (argument[0] == '.')
		mfl = build_mf_lst(lad, patterns, argument);
	else
		mfl = build_mf_lst(ld, patterns, argument);
	free_tabstr(patterns);
	return (mfl);
}
