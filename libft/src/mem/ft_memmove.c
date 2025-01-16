/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:42:06 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/16 11:15:46 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ldest;
	char		*lsrc;
	size_t		i;

	if (!src && !dest)
		return (NULL);
	ldest = (char *)dest;
	lsrc = (char *)src;
	if (ldest > lsrc)
	{
		while (n-- > 0)
			ldest[n] = lsrc[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			ldest[i] = lsrc[i];
			i++;
		}
	}
	return (ldest);
}
