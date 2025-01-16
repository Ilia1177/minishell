/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:58:50 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/09 18:50:22 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c_check;

	c_check = c;
	while (*s)
	{
		if (*s == c_check)
			return ((char *)s);
		s++;
	}
	if (c_check == '\0')
		return ((char *)s);
	return (NULL);
}
