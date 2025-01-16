/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:33:57 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/17 12:58:42 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_checklen(size_t len)
{
	char	*str;

	if (len == 0)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
		return (str);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (!s)
		return (NULL);
	if (len == 0)
		return (ft_checklen(len));
	s_len = ft_strlen(s);
	if (s_len == 0 || start >= s_len)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
		return (str);
	}
	if (s_len - start < len)
		len = s_len - start ;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	len = ft_strlcpy(str, s + start, len + 1);
	return (str);
}
