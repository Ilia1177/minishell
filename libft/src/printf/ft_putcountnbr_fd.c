/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcountnbr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:49:43 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/21 20:46:10 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcountnbr_fd(int n, int fd)
{
	long	num;
	char	cnum;
	int		count;

	count = 1;
	num = n;
	if (num == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		count = 11;
	}
	else
	{
		if (num < 0)
		{
			num *= -1;
			write(fd, "-", 1);
			count += 1;
		}
		if (num >= 10)
			count += ft_putcountnbr_fd(num / 10, fd);
		cnum = (num % 10) + '0';
		write(fd, &cnum, 1);
	}
	return (count);
}
