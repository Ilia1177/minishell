/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:01 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/16 11:17:01 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		str_len;

	if (!s1 || !set)
		return (NULL);
	if (!*s1)
	{
		str = ft_calloc(1, sizeof(char));
		return (str);
	}
	str_len = ft_strlen(s1);
	i = 0;
	while (ft_isset(s1[i], set) && s1 [i])
		i++;
	j = str_len - 1;
	while (ft_isset(s1[j], set))
		j--;
	str = ft_substr(s1, i, str_len - i - (str_len - j) + 1);
	if (!str)
		return (NULL);
	return (str);
}
