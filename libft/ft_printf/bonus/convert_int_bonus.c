/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_int_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	int_sign_char(int n, t_fmt *fmt)
{
	if (n < 0)
		return ('-');
	if (fmt->flag_plus)
		return ('+');
	if (fmt->flag_space)
		return (' ');
	return (0);
}

static int	int_content_len(int n, t_fmt *fmt)
{
	unsigned long	abs_val;
	int				dlen;
	int				len;

	if (fmt->prec == 0 && n == 0)
	{
		if (int_sign_char(n, fmt))
			return (1);
		return (0);
	}
	if (n < 0)
		abs_val = (unsigned long)(-(long)n);
	else
		abs_val = (unsigned long)n;
	dlen = pf_nbrlen_base(abs_val, 10);
	len = dlen;
	if (fmt->prec > dlen)
		len = fmt->prec;
	if (int_sign_char(n, fmt))
		len++;
	return (len);
}

static int	print_int_core(int n, t_fmt *fmt, int prec)
{
	int				count;
	unsigned long	abs_val;
	int				sign;
	int				dlen;

	if (n < 0)
		abs_val = (unsigned long)(-(long)n);
	else
		abs_val = (unsigned long)n;
	count = 0;
	sign = int_sign_char(n, fmt);
	if (sign)
		count += pf_putchar(sign);
	dlen = pf_nbrlen_base(abs_val, 10);
	count += pf_pad_width(prec, dlen, '0');
	if (!(prec == 0 && n == 0))
		count += pf_putnbr_base(abs_val, "0123456789", 10);
	return (count);
}

int	convert_int(t_fmt *fmt, va_list *ap)
{
	int	n;
	int	len;
	int	count;
	int	zprec;

	n = va_arg(*ap, int);
	len = int_content_len(n, fmt);
	count = 0;
	if (fmt->flag_zero && fmt->width > len)
	{
		zprec = fmt->width - (int_sign_char(n, fmt) != 0);
		return (print_int_core(n, fmt, zprec));
	}
	if (!fmt->flag_minus)
		count += pf_pad_width(fmt->width, len, ' ');
	count += print_int_core(n, fmt, fmt->prec);
	if (fmt->flag_minus)
		count += pf_pad_width(fmt->width, len, ' ');
	return (count);
}
