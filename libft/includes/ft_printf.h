/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:23:01 by jhervoch          #+#    #+#             */
/*   Updated: 2024/12/03 10:31:01 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(int fd, const char *format, ...);
int		ft_putcountunbr_fd(unsigned int n, int fd);
int		ft_putcounthex_fd(unsigned int n, int fd, int up);
int		ft_putcountnbr_fd(int n, int fd);
int		ft_putcountchar_fd(char c, int fd);
int		ft_putcountstr_fd(char *str, int fd);
int		ft_putcountptr_fd(void *ptr, int fd);

#endif
