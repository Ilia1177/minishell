/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:38:46 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/09 20:12:36 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*src_new;
	int		src_size;
	int		i;

	src_size = ft_strlen(s);
	src_new = malloc (sizeof * src_new * (src_size + 1));
	if (src_new == NULL)
		return (NULL);
	i = 0;
	while (i < src_size)
	{
		src_new[i] = s[i];
		i++;
	}
	src_new[i] = '\0';
	return (src_new);
}
