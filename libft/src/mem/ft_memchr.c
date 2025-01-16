/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:20:07 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/09 18:51:01 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		c_check;
	unsigned int		i;

	i = 0 ;
	str = s;
	c_check = c;
	while (i < n)
	{
		if (*str == c_check)
			return (((void *)str));
		str++;
		i++;
	}
	return (NULL);
}
