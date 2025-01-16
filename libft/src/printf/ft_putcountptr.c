/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcountptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:16:22 by jhervoch          #+#    #+#             */
/*   Updated: 2024/12/03 10:32:37 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putcounthexptr(unsigned long add, int fd)
{
	int		count;
	char	cnum;
	char	*base;

	count = 1;
	base = "0123456789abcdef";
	if (add >= 16)
	{
		count += ft_putcounthexptr(add / 16, fd);
	}
	cnum = base[add % 16];
	write(fd, &cnum, 1);
	return (count);
}

int	ft_putcountptr_fd(void *ptr, int fd)
{
	unsigned long int	add;
	int					count;

	if (!ptr)
	{
		count = ft_putcountstr_fd("(nil)", fd);
		return (count);
	}
	add = (unsigned long)ptr;
	count = ft_putcountstr_fd("0x", fd);
	count += ft_putcounthexptr(add, fd);
	return (count);
}
