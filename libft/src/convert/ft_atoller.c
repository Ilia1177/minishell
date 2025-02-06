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

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int64_t	ft_atoller(const char *nptr, int *error)
{
	int64_t	sign;
	int64_t nbr;

	nbr = 0;
	sign = 1;
	*error = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		nbr *= 10;
		nbr += *nptr - '0';
		if (nbr < 0 || (nbr * sign) < LLONG_MIN || (nbr * sign) > LLONG_MAX)
			*error = 1;
		nptr++;
	}
	return (nbr * sign);
}
