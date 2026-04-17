/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	init_fmt(t_fmt *fmt)
{
	fmt->spec = 0;
	fmt->width = 0;
	fmt->prec = -1;
	fmt->flag_minus = 0;
	fmt->flag_zero = 0;
	fmt->flag_hash = 0;
	fmt->flag_plus = 0;
	fmt->flag_space = 0;
}

static const char	*parse_flags(t_fmt *fmt, const char *ptr)
{
	while (*ptr == '-' || *ptr == '0' || *ptr == '#'
		|| *ptr == '+' || *ptr == ' ')
	{
		if (*ptr == '-')
			fmt->flag_minus = 1;
		else if (*ptr == '0')
			fmt->flag_zero = 1;
		else if (*ptr == '#')
			fmt->flag_hash = 1;
		else if (*ptr == '+')
			fmt->flag_plus = 1;
		else if (*ptr == ' ')
			fmt->flag_space = 1;
		ptr++;
	}
	return (ptr);
}

static const char	*parse_width(t_fmt *fmt, const char *ptr)
{
	while (*ptr >= '0' && *ptr <= '9')
	{
		fmt->width = fmt->width * 10 + (*ptr - '0');
		ptr++;
	}
	return (ptr);
}

static const char	*parse_prec(t_fmt *fmt, const char *ptr)
{
	if (*ptr != '.')
		return (ptr);
	ptr++;
	fmt->prec = 0;
	while (*ptr >= '0' && *ptr <= '9')
	{
		fmt->prec = fmt->prec * 10 + (*ptr - '0');
		ptr++;
	}
	return (ptr);
}

const char	*parse_format(t_fmt *fmt, const char *ptr)
{
	init_fmt(fmt);
	ptr = parse_flags(fmt, ptr);
	ptr = parse_width(fmt, ptr);
	ptr = parse_prec(fmt, ptr);
	if (fmt->flag_minus)
		fmt->flag_zero = 0;
	if (fmt->prec >= 0)
		fmt->flag_zero = 0;
	if (fmt->flag_plus)
		fmt->flag_space = 0;
	fmt->spec = *ptr;
	if (*ptr)
		ptr++;
	return (ptr);
}
