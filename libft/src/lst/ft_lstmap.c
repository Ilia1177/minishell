/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:45:23 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/16 17:42:42 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token	*ft_lstmap(t_token *lst, void *(*f)(char **), void (*del)(char **))
{
	t_token	*new_list;
	t_token	*iterator;
	t_token	*elem;
	char	**content;

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
