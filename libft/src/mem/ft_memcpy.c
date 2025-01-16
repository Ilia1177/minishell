/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:57:17 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/15 21:58:47 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ldest;
	const char	*lsrc;
	size_t		i;

	if (!dest && !src)
		return (0);
	ldest = dest;
	lsrc = src;
	i = 0;
	while (i < n)
	{
		*(ldest + i) = *(lsrc + i);
		i++;
	}
	return (ldest);
}
