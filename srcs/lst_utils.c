/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:47:30 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/05 12:41:48 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_token(t_token *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (lst->input)
		(*del)(lst->input);
	lst->input = NULL;
	if (lst->cmd)
		free_cmd(lst->cmd);
	free(lst);
}

void	ft_lstclear_token(t_token **lst, void (*del)(void*))
{
	t_token	*previous;
	t_token	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		previous = current;
		current = current->next;
		ft_lstdelone_token(previous, del);
	}
	*lst = NULL;
}

void	ft_lst_split_dup(t_token **lst, int (*f)(char *, char *, char *), char *cmp)
{
	t_token	*current;
	t_token	*new;
	t_token	*next;
	char	dup[2];
	int		nb_cmp;

	current = *lst;
	dup[0] = '\0';
	dup[1] = '\0';
	while (current)
	{
		nb_cmp = (*f)(current->input, cmp, dup);
		if (ft_strchr(current->input, '\"'))
			nb_cmp = 0;
		next = current->next;
		while (nb_cmp-- > 0)
		{
			new = make_token(dup);
			current->input = ft_strdup(dup);
			new->next = current->next;
			current->next = new;
			next = new->next;
		}
		current = next;
	}
}

int	ft_count_dup(char *s1, char *s2, char *dup)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (s1[i])
	{
		j = -1;
		while (s2[++j])
		{
			while (s1[i] && s1[i] == s2[j])
			{
				count++;
				i++;
				dup[0] = s2[j];
			}
		}
		if (s1[i])
			i++;
	}
	return (count);
}

void	iter_split_args(char *input, t_token **iter_token, int nb_args)
{
	int		i;
	t_token	*token;

	token = *iter_token;
	i = 0;
	while (*input && i < nb_args)
	{
		while (*input && is_space(*input) && !ft_isquote(*input))
			input++;
		token->cmd->args[i] = ft_calloc(arg_len(input) + 1, sizeof(char));
		if (!token->cmd->args[i])
		{
			ft_free_bugsplit(token->cmd->args, i - 1);
			return ;
		}
		ft_strlcpy(token->cmd->args[i], input, arg_len(input) + 1);
		input += arg_len(input);
		i++;
	}
}
