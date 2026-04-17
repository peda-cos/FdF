/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_printf(const char *fmt_str, ...)
{
	va_list	ap;
	t_fmt	fmt;
	int		count;
	int		ret;

	if (!fmt_str)
		return (-1);
	count = 0;
	va_start(ap, fmt_str);
	while (*fmt_str)
	{
		if (*fmt_str == '%')
		{
			fmt_str = parse_format(&fmt, fmt_str + 1);
			ret = dispatch(&fmt, &ap);
		}
		else
			ret = (int)write(1, fmt_str++, 1);
		if (ret == -1)
			return (va_end(ap), -1);
		count += ret;
	}
	va_end(ap);
	return (count);
}
