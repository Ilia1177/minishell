/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:24:20 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/16 10:27:58 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!little && !len) || (!big && !len))
		return (NULL);
	if (!little[0])
		return (((char *)big));
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && big[i + j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return (((char *)(big + i)));
		i++;
	}
	return (NULL);
}
