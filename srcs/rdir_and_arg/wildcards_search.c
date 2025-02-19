/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:43:06 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/19 16:59:32 by jhervoch         ###   ########.fr       */
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
		*file_str = tmp_str;
		free(tmp_str);
		*nb_find += 1;
		return (1);
	}
	free(tmp_str);
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
		*file_str = tmp_str;
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
		*file_str = tmp_str;
		free(tmp_str);
		*nb_find += 1;
		return (1);
	}
	return (0);
}
