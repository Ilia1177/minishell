/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:11:58 by jhervoch          #+#    #+#             */
/*   Updated: 2025/01/22 23:04:59 by ilia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *s, int c)
{
	int	strlen;

	strlen = 0;
	while (s[strlen] != '\0' && s[strlen] != c)
		strlen++;
	return (strlen);
}

size_t	ft_strlen(const char *s)
{
	int	strlen;

	strlen = 0;
	while (s[strlen] != '\0')
		strlen++;
	return (strlen);
}
