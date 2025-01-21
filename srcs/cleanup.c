/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:45:27 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/21 16:13:52 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tabstr(char **tabstr);
static void	ft_lstclear_token(t_token **lst, void (*del)(void*));

void	free_elem(void *elem, t_mem_type mem)
{
	if (mem == PTR || mem == S_TAB)
		free(elem);
	else if (mem == D_TAB)
	{
		free_tabstr(elem);
	}
	else if (mem == LST)
		ft_lstclear_token(elem, &free);
}

void	free_tabstr(char **tabstr)
{
	size_t	i;

	i = 0;
	while (tabstr[i])
	{
		free (tabstr[i]);
		++i;
	}
	free (tabstr);
}

static void	ft_lstdelone_token(t_token *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->input);
	free(lst);
}

static void	ft_lstclear_token(t_token **lst, void (*del)(void*))
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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = (t_list *) malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}
