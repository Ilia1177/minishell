/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:10:42 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 23:14:57 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"
#include "parsing.h"

/****************************************************
 * replacing wildcards args with matching files
 * and return the index of the next arg
 * *************************************************/
int	replacing_wildcards(t_token *token, int index, t_list *mfl)
{
	char	**new_args;
	char	**old_args;
	int		nb_arg;
	t_list	*ref_mfl;

	ref_mfl = mfl;
	old_args = token->cmd->args;
	nb_arg = count_args(token->cmd->args) + ft_lstsize(mfl);
	new_args = ft_calloc(sizeof (char *), nb_arg + 1);
	nb_arg = -1;
	while (++nb_arg < index)
		new_args[nb_arg] = ft_strdup(old_args[nb_arg]);
	while (ref_mfl)
	{
		new_args[nb_arg] = ft_strdup((char *)ref_mfl->content);
		nb_arg++;
		ref_mfl = ref_mfl->next;
	}
	while (old_args[++index])
		new_args[nb_arg++] = ft_strdup(old_args[index]);
	free_tabstr(token->cmd->args);
	token->cmd->args = new_args;
	return (ft_lstsize(mfl) - 1);
}

/****************************************************
 * build a list of all filename in current directory
 * *************************************************/
void	build_list_all_dir(t_list **list)
{
	t_list			*elem;
	DIR				*dir;
	struct dirent	*dr;
	char			*file_name;

	if (access(".", F_OK))
		return ;
	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
	dr = readdir(dir);
	while (dr)
	{
		file_name = ft_strdup(dr->d_name);
		elem = ft_lstnew((void *)file_name);
		ft_lstadd_back(list, elem);
		dr = readdir(dir);
	}
	closedir(dir);
	sort_list_dir(list);
}

/****************************************************
 * return the file name matching the wildcards pattens
 * elem of matching files list
 * @param file_name name of file
 * @param patterns the wildcard pattern
 * @paran nb_pat number of string separate by *
 * @param str the wildcard input
 * *************************************************/
t_list	*matching_file(char **file_name, char **patterns, int nb_pat, char *str)
{
	int		i;
	int		not_find;
	int		nb_find;
	char	*tmp_name;
	t_list	*elem;

	elem = NULL;
	i = -1;
	not_find = 1;
	nb_find = 0;
	tmp_name = ft_strdup(*file_name);
	while (patterns[++i] && not_find)
	{
		if (i == 0 && str[i] != '*')
			not_find = begin_search(file_name, patterns[i], &nb_find);
		else if (i == nb_pat - 1 && str[ft_strlen(str) - 1] != '*')
			not_find = end_search(file_name, patterns[i], &nb_find);
		else
			not_find = middle_search(file_name, patterns[i], &nb_find);
		if (nb_find == nb_pat)
			elem = ft_lstnew((void *)tmp_name);
	}
	if (!not_find)
		free(tmp_name);
	return (elem);
}

/****************************************************
 * build the list of all files in current directory
 * matching the wildcards pattern
 * *************************************************/
t_list	*build_mf_lst(t_list *list, char **patterns, char *str)
{
	char	*file_name;
	t_list	*lst_dir;
	t_list	*match_files_lst;
	t_list	*elem;
	int		nb_pat;

	nb_pat = 0;
	while (patterns[nb_pat])
		nb_pat++;
	remove_pattern_quote(&patterns);
	lst_dir = list;
	match_files_lst = NULL;
	while (lst_dir)
	{
		file_name = NULL;
		file_name = ft_strdup((char *)lst_dir->content);
		elem = matching_file(&file_name, patterns, nb_pat, str);
		if (elem)
			ft_lstadd_back(&match_files_lst, elem);
		lst_dir = lst_dir->next;
		free(file_name);
	}
	return (match_files_lst);
}

/****************************************************
 * build the list of all files of current directory
 * except hidden files
 * *************************************************/
t_list	*build_list_dir(t_list *list)
{
	char	*file_name;
	t_list	*lst_dir;
	t_list	*match_files_lst;
	t_list	*elem;

	lst_dir = list;
	match_files_lst = NULL;
	while (lst_dir)
	{
		if (*(char *)lst_dir->content != '.')
		{
			file_name = ft_strdup((char *)lst_dir->content);
			elem = ft_lstnew((void *)file_name);
			ft_lstadd_back(&match_files_lst, elem);
		}
		lst_dir = lst_dir->next;
	}
	return (match_files_lst);
}
