/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcounthex_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:07:43 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/21 20:00:12 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcounthex_fd(unsigned int n, int fd, int up)
{
	char	cnum;
	char	*base;
	int		count;

	count = 1;
	if (up)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
	{
		count += ft_putcounthex_fd(n / 16, fd, up);
	}
	cnum = base[n % 16];
	write(fd, &cnum, 1);
	return (count);
}
