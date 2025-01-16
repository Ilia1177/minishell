/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:34:06 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/15 11:46:43 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	cnum;

	num = n;
	if (num == INT_MIN)
		write(fd, "-2147483648", 11);
	else
	{
		if (num < 0)
		{
			num *= -1;
			write(fd, "-", 1);
		}
		if (num >= 10)
			ft_putnbr_fd(num / 10, fd);
		cnum = (num % 10) + '0';
		write(fd, &cnum, 1);
	}
}
