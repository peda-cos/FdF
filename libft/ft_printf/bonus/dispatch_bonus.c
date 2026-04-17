/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	dispatch(t_fmt *fmt, va_list *ap)
{
	if (fmt->spec == 'c')
		return (convert_char(fmt, ap));
	else if (fmt->spec == 's')
		return (convert_str(fmt, ap));
	else if (fmt->spec == 'p')
		return (convert_ptr(fmt, ap));
	else if (fmt->spec == 'd' || fmt->spec == 'i')
		return (convert_int(fmt, ap));
	else if (fmt->spec == 'u')
		return (convert_uint(fmt, ap));
	else if (fmt->spec == 'x' || fmt->spec == 'X')
		return (convert_hex(fmt, ap));
	else if (fmt->spec == '%')
		return (convert_percent(fmt));
	return (0);
}
