/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:28:50 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/17 18:48:54 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlowercmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((unsigned char)ft_tolower(s1[i]) && (unsigned char)ft_tolower(s2[i])
		&& (unsigned char)ft_tolower(s1[i]) == (unsigned char)ft_tolower(s2[i]))
		i++;
	return ((unsigned char)ft_tolower(s1[i])
		- (unsigned char)ft_tolower(s2[i]));
}
