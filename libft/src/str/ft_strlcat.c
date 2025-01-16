/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:53:38 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/14 10:57:15 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	total_size;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	total_size = src_len + size;
	if (size != 0 && size > dst_len)
	{
		i = 0;
		while (i < (size - dst_len - 1) && src[i] != '\0')
		{
			dst[dst_len + i] = src [i];
			i++;
		}
		dst[dst_len + i] = '\0';
		total_size = dst_len + src_len;
	}
	return (total_size);
}
