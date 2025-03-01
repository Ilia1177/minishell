/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:06:48 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 23:12:59 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "rdir_and_arg.h"

/****************************************************
 * Sort the current directory list
 * before the first wildcards *
 * update the file name after substr -> after pattern
 * returns 1 if the pattern found
 * *************************************************/
void	sort_list_dir(t_list **list)
{
	t_list	*current;
	t_list	*next;
	char	*curr_str;
	char	*next_str;

	current = *list;
	while (current)
	{
		next = current->next;
		while (next)
		{
			curr_str = (char *)current->content;
			next_str = (char *)next->content;
			if (next && ft_strlowercmp(curr_str, next_str) > 0)
			{
				curr_str = (char *)current->content;
				current->content = next->content;
				next->content = curr_str;
			}
			next = next->next;
		}
		current = current->next;
	}
}

static int	only_wild(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '*')
			return (0);
		str++;
	}
	return (1);
}

static int	is_wildcard(char *str)
{
	int	quoted;

	quoted = -1;
	if (!str || !ft_strchr(str, '*') || !ft_strcmp(str, "*."))
		return (0);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			quoted *= -1;
		if (quoted == 1 && *str == '*')
			return (0);
		str++;
	}
	return (1);
}

/****************************************************
 * loop each args
 * @param mfl - match_files_lst
 * @param lad - list_all_dir
 * @param ld - list_dir
 * *************************************************/
static void	wild_arg_loop(t_token *token, t_list *mfl, t_list *lad, t_list *ld)
{
	int		i;

	i = 0;
	if (!token->cmd->args[0] || !token->cmd->args[1])
		return ;
	while (token->cmd->args[++i])
	{
		if (!is_wildcard(token->cmd->args[i]))
			continue ;
		else if (only_wild(token->cmd->args[i]))
			mfl = build_list_dir(lad);
		else
			mfl = build_from_pattern(lad, ld, token->cmd->args[i]);
		if (mfl)
		{
			i += replacing_wildcards(token, i, mfl);
			ft_lstclear(&mfl, free);
		}
	}
}

/****************************************************
 * main wildcards function
 * *************************************************/
void	wildcards(t_token *token, t_data *data)
{
	t_list	*list_all_dir;
	t_list	*list_dir;
	t_list	*match_files_lst;

	(void)data;
	if (!token->cmd)
		return ;
	match_files_lst = NULL;
	list_all_dir = NULL;
	list_dir = NULL;
	build_list_all_dir(&list_all_dir);
	list_dir = build_list_dir(list_all_dir);
	wild_arg_loop(token, match_files_lst, list_all_dir, list_dir);
	ft_lstclear(&match_files_lst, free);
	ft_lstclear(&list_dir, free);
	ft_lstclear(&list_all_dir, free);
}
