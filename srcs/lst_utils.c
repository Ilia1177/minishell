/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:47:30 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/02 10:24:12 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front_mem(t_mem **lst, t_mem *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_mem	*ft_lstnew_mem(void *elem, t_mem_type type)
{
	t_mem	*new_elem;

	new_elem = (t_mem *) malloc(sizeof(t_mem));
	if (!new_elem)
		return (NULL);
	new_elem->elem = elem;
	new_elem->type = type;
	new_elem->next = NULL;
	return (new_elem);
}

void	ft_lstdelone_token(t_token *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
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
	int		i;

	current = *lst;
	dup[0] = '\0'; 
	dup[1] = '\0'; 
	while (current)
	{
		nb_cmp = (*f)(current->input, cmp, dup);
		if (ft_strchr(current->input, '\"'))
			nb_cmp = 0;
		i = 0;
		next = current->next;
		while (++i < nb_cmp)
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

int	ft_count_dup(char *s1 , char *s2 , char *dup)
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
