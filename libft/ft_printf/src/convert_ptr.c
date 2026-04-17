/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_ptr(t_fmt *fmt, va_list *ap)
{
	void			*ptr;
	int				count;

	(void)fmt;
	ptr = va_arg(*ap, void *);
	if (!ptr)
		return (ft_putstr_fd("(nil)", 1));
	count = ft_putstr_fd("0x", 1);
	count += ft_putnbr_base((unsigned long)ptr, "0123456789abcdef", 16);
	return (count);
}
