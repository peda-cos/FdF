/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	convert_char(t_fmt *fmt, va_list *ap)
{
	char	c;
	int		count;

	c = (char)va_arg(*ap, int);
	count = 0;
	if (!fmt->flag_minus && fmt->width > 1)
		count += pf_pad_width(fmt->width, 1, ' ');
	count += pf_putchar(c);
	if (fmt->flag_minus && fmt->width > 1)
		count += pf_pad_width(fmt->width, 1, ' ');
	return (count);
}

static int	str_effective_len(const char *s, int prec)
{
	int	len;

	len = pf_strlen(s);
	if (prec >= 0 && prec < len)
		len = prec;
	return (len);
}

int	convert_str(t_fmt *fmt, va_list *ap)
{
	char	*s;
	int		len;
	int		count;

	s = va_arg(*ap, char *);
	if (!s)
		s = "(null)";
	len = str_effective_len(s, fmt->prec);
	count = 0;
	if (!fmt->flag_minus && fmt->width > len)
		count += pf_pad_width(fmt->width, len, ' ');
	count += pf_putstr_n(s, len);
	if (fmt->flag_minus && fmt->width > len)
		count += pf_pad_width(fmt->width, len, ' ');
	return (count);
}

int	convert_percent(t_fmt *fmt)
{
	int	count;

	count = 0;
	if (!fmt->flag_minus && fmt->width > 1)
		count += pf_pad_width(fmt->width, 1, ' ');
	count += pf_putchar('%');
	if (fmt->flag_minus && fmt->width > 1)
		count += pf_pad_width(fmt->width, 1, ' ');
	return (count);
}
