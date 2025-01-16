/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:38:18 by jhervoch          #+#    #+#             */
/*   Updated: 2024/12/03 10:33:38 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_specifier(const char *format, va_list sp, int *count, int fd)
{
	if (*format == 'c')
		*count += ft_putcountchar_fd((char)va_arg(sp, int), fd);
	if (*format == 's')
		*count += ft_putcountstr_fd((char *)va_arg(sp, char *), fd);
	if ((*format == 'd') || (*format == 'i'))
		*count += ft_putcountnbr_fd(va_arg(sp, int), fd);
	if (*format == 'u')
		*count += ft_putcountunbr_fd(va_arg(sp, unsigned int), fd);
	if (*format == 'x')
		*count += ft_putcounthex_fd(va_arg(sp, unsigned int), fd, 0);
	if (*format == 'X')
		*count += ft_putcounthex_fd(va_arg(sp, unsigned int), fd, 1);
	if (*format == '%')
		*count += ft_putcountchar_fd('%', fd);
	if (*format == 'p')
		*count += ft_putcountptr_fd(va_arg(sp, void *), fd);
}

int	ft_printf(int fd, const char *format, ...)
{
	int		count;
	va_list	specifier;

	if (!format)
		return (-1);
	va_start(specifier, format);
	count = 0;
	while (*format)
	{
		while (*format != '%' && *format)
		{
			write(fd, format++, 1);
			count++;
		}
		if (*format)
			check_specifier(++format, specifier, &count, fd);
		if (*format)
			format++;
	}
	va_end(specifier);
	return (count);
}
