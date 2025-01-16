/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcountcstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:57:15 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/21 20:53:43 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h" 

int	ft_putcountchar_fd(char c, int fd)
{
	int	count;

	count = 1;
	write(fd, &c, 1);
	return (count);
}

int	ft_putcountstr_fd(char *str, int fd)
{
	int		count;
	char	*nullstr;

	nullstr = "(null)";
	count = 0;
	if (!str)
		str = nullstr;
	while (*str)
	{
		write(fd, str++, 1);
		count++;
	}
	return (count);
}
