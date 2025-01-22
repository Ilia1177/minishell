/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:45:27 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/22 09:38:03 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_elem(void *elem, t_mem_type mem)
{
	t_token	*lst;

	lst = elem;
	if (mem == PTR)
		free(elem);
	else if (mem == D_TAB)
	{
		free_tabstr(elem);
	}
	else if (mem == LST)
		ft_lstclear_token(&lst, &free);
}
