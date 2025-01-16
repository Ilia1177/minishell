/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:03:50 by jhervoch          #+#    #+#             */
/*   Updated: 2024/10/16 11:15:06 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_size(unsigned int n)
{
	int	num_size;

	num_size = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		num_size++;
	}
	return (num_size);
}

static long	check_number(int n, int *num_size)
{
	long	number;

	number = n;
	*num_size = 0;
	if (n < 0)
	{
		number *= -1;
		*num_size = 1;
	}
	*num_size += ft_int_size(number);
	return (number);
}

char	*ft_itoa(int n)
{
	int		num_size;
	char	*num;
	int		i;
	long	number;

	i = 0;
	number = check_number(n, &num_size);
	num = (char *)ft_calloc(num_size + 1, (sizeof(char)));
	if (!num)
		return (NULL);
	if (n < 0)
	{
		num[0] = '-';
		i++;
	}
	num_size--;
	while (num_size >= i)
	{
		num[num_size] = (number % 10) + '0';
		number = number / 10;
		num_size--;
	}
	return (num);
}
