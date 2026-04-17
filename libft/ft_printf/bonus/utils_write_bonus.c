/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	pf_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	pf_putchar(char c)
{
	return ((int)write(1, &c, 1));
}

int	pf_putstr(const char *s)
{
	if (!s)
		return (0);
	return ((int)write(1, s, pf_strlen(s)));
}

int	pf_putstr_n(const char *s, int n)
{
	if (!s || n <= 0)
		return (0);
	return ((int)write(1, s, n));
}

int	pf_pad_width(int total_width, int content_len, char fill)
{
	int	count;
	int	pad;

	count = 0;
	pad = total_width - content_len;
	while (pad > 0)
	{
		count += pf_putchar(fill);
		pad--;
	}
	return (count);
}
