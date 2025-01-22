/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:47:30 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/21 17:06:23 by jhervoch         ###   ########.fr       */
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
