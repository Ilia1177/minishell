/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:45:23 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/17 16:34:32 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*iterator;
	t_list	*elem;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	iterator = lst;
	while (iterator)
	{
		content = f(iterator->content);
		elem = ft_lstnew(content);
		if (!elem)
		{
			del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, elem);
		iterator = iterator->next;
	}
	return (new_list);
}
