/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:06:48 by jhervoch          #+#    #+#             */
/*   Updated: 2025/03/01 13:27:11 by npolack          ###   ########.fr       */
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
	char	**patterns;
	int		i;

	i = 0;
	if (!token->cmd->args[1])
		return ;
	while (token->cmd->args[++i])
	{
		
		ft_printf(2, "%s->cmd->args[%d]: %s\n", token->input, i, token->cmd->args[i]);
		if (!is_wildcard(token->cmd->args[i]))
		{
			continue ;
		}
		else if (only_wild(token->cmd->args[i]))
		{
			mfl = build_list_dir(lad);
		}
		else
		{
			patterns = ft_split(token->cmd->args[i], '*');
			if (token->cmd->args[i][0] == '.')
				mfl = build_mf_lst(lad, patterns, token->cmd->args[i]);
			else
				mfl = build_mf_lst(ld, patterns, token->cmd->args[i]);
			free_tabstr(patterns);
		}
		if (mfl)
		{

			i += replacing_wildcards(token, i, mfl);
			ft_printf(2, "replacing_wildcard i=%d\n", i);
			ft_lstclear(&mfl, free);
		}
	}
}
void print_lst(t_list *lst, t_data *data)
{
	(void)data;
	while (lst)
	{
		ft_printf(2, "%s\n", (char *)lst->content);
		lst = lst->next;
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
	data->flag = 1;
	if (!token->cmd)
		return ;
	match_files_lst = NULL;
	list_all_dir = NULL;
	list_dir = NULL;

	build_list_all_dir(&list_all_dir);
	list_dir = build_list_dir(list_all_dir);
	ft_printf(2, "list all dir ==\n");
	print_lst(list_all_dir, data);
	ft_printf(2, "list dir ==\n");
	print_lst(list_dir, data);
	ft_printf(2, "match_files_lst ==\n");
	print_lst(match_files_lst, data);
	wild_arg_loop(token, match_files_lst, list_all_dir, list_dir);
	ft_printf(2, "after wild_arg_loop\n");
	ft_lstclear(&match_files_lst, free);
	ft_lstclear(&list_dir, free);
	ft_lstclear(&list_all_dir, free);
	data->flag = 0;
}
