/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen_base(unsigned long n, int blen)
{
	int	len;

	len = 1;
	while (n >= (unsigned long)blen)
	{
		n /= blen;
		len++;
	}
	return (len);
}

int	ft_putnbr_base(unsigned long n, char *base, int blen)
{
	int	count;

	if (blen < 2)
		return (0);
	count = 0;
	if (n >= (unsigned long)blen)
		count += ft_putnbr_base(n / blen, base, blen);
	count += ft_putchar_fd(base[n % blen], 1);
	return (count);
}
