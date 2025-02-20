/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:51:38 by jhervoch          #+#    #+#             */
/*   Updated: 2025/02/06 15:11:43 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdio.h>

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	is_neg(const char *nptr, int64_t *sign, int64_t *neg)
{
	*neg = 0;
	*sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
		{
			*sign = -1;
			*neg = 1;
		}
	}
}

int64_t	ft_atoller(const char *nptr, int *error)
{
	int64_t	sign;
	int64_t	nbr;
	int64_t	neg;
	int64_t	digit;

	nbr = 0;
	*error = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	is_neg(nptr, &sign, &neg);
	if (neg)
		nptr++;
	while (*nptr && ft_isdigit(*nptr))
	{
		digit = *nptr - '0';
		if ((nbr > LLONG_MAX / 10)
			|| ((nbr == LLONG_MAX / 10) && (digit > LLONG_MAX % 10 + neg)))
			*error = 1;
		nbr = nbr * 10 + digit;
		nptr++;
	}
	return (nbr * sign);
}
