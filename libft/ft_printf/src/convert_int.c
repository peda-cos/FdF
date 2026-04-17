/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_int(t_fmt *fmt, va_list *ap)
{
	int				n;
	int				count;
	unsigned long	abs_val;

	(void)fmt;
	n = va_arg(*ap, int);
	count = 0;
	if (n < 0)
	{
		count += ft_putchar_fd('-', 1);
		abs_val = (unsigned long)(-(long)n);
	}
	else
		abs_val = (unsigned long)n;
	count += ft_putnbr_base(abs_val, "0123456789", 10);
	return (count);
}
