/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcountunbr_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:07:43 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/21 19:25:55 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putcountunbr_fd(unsigned int n, int fd)
{
	char	cnum;
	int		count;

	count = 1;
	if (n >= 10)
		count += ft_putcountunbr_fd(n / 10, fd);
	cnum = (n % 10) + '0';
	write(fd, &cnum, 1);
	return (count);
}
