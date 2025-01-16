/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:58:50 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/09 18:55:28 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				str_len;
	unsigned char	c_check;

	c_check = c;
	str_len = ft_strlen(s);
	i = str_len;
	if (c_check == '\0')
		return ((char *)(s + i));
	while (i >= 0)
	{
		if (s[i] == c_check)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
