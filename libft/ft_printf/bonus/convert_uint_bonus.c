/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_uint_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	uint_content_len(t_fmt *fmt, unsigned long val, int blen)
{
	int	dlen;
	int	len;
	int	pfx;

	pfx = 0;
	if (fmt->flag_hash && val != 0 && blen == 16)
		pfx = 2;
	if (fmt->prec == 0 && val == 0)
		return (pfx);
	dlen = pf_nbrlen_base(val, blen);
	len = dlen;
	if (fmt->prec > dlen)
		len = fmt->prec;
	return (len + pfx);
}

static int	print_uint_core(t_fmt *fmt, unsigned long val, char *base, int prec)
{
	int	count;
	int	dlen;
	int	blen;

	blen = pf_strlen(base);
	count = 0;
	if (fmt->flag_hash && val != 0 && blen == 16)
	{
		count += pf_putchar('0');
		if (fmt->spec == 'X')
			count += pf_putchar('X');
		else
			count += pf_putchar('x');
	}
	dlen = pf_nbrlen_base(val, blen);
	count += pf_pad_width(prec, dlen, '0');
	if (!(prec == 0 && val == 0))
		count += pf_putnbr_base(val, base, blen);
	return (count);
}

static int	put_uint_full(t_fmt *fmt, unsigned long val, char *base, int blen)
{
	int	len;
	int	count;
	int	pfx;
	int	zprec;

	pfx = 0;
	if (fmt->flag_hash && val != 0 && blen == 16)
		pfx = 2;
	len = uint_content_len(fmt, val, blen);
	count = 0;
	if (fmt->flag_zero && fmt->width > len)
	{
		zprec = fmt->width - pfx;
		return (print_uint_core(fmt, val, base, zprec));
	}
	if (!fmt->flag_minus)
		count += pf_pad_width(fmt->width, len, ' ');
	count += print_uint_core(fmt, val, base, fmt->prec);
	if (fmt->flag_minus)
		count += pf_pad_width(fmt->width, len, ' ');
	return (count);
}

int	convert_uint(t_fmt *fmt, va_list *ap)
{
	unsigned long	val;

	val = (unsigned long)va_arg(*ap, unsigned int);
	return (put_uint_full(fmt, val, "0123456789", 10));
}

int	convert_hex(t_fmt *fmt, va_list *ap)
{
	unsigned long	val;
	char			*base;

	val = (unsigned long)va_arg(*ap, unsigned int);
	if (fmt->spec == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	return (put_uint_full(fmt, val, base, 16));
}
