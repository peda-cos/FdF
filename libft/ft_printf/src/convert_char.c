/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_char(t_fmt *fmt, va_list *ap)
{
	char	c;

	(void)fmt;
	c = (char)va_arg(*ap, int);
	return (ft_putchar_fd(c, 1));
}

int	convert_str(t_fmt *fmt, va_list *ap)
{
	char	*s;

	(void)fmt;
	s = va_arg(*ap, char *);
	if (!s)
		return (ft_putstr_fd("(null)", 1));
	return (ft_putstr_fd(s, 1));
}

int	convert_percent(t_fmt *fmt)
{
	(void)fmt;
	return (ft_putchar_fd('%', 1));
}
