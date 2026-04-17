/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_uint(t_fmt *fmt, va_list *ap)
{
	unsigned int	val;

	(void)fmt;
	val = va_arg(*ap, unsigned int);
	return (ft_putnbr_base((unsigned long)val, "0123456789", 10));
}

int	convert_hex(t_fmt *fmt, va_list *ap)
{
	unsigned int	val;
	char			*base;

	val = va_arg(*ap, unsigned int);
	if (fmt->spec == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	return (ft_putnbr_base((unsigned long)val, base, 16));
}
