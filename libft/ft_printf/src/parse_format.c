/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

const char	*parse_format(t_fmt *fmt, const char *ptr)
{
	init_fmt(fmt);
	fmt->spec = *ptr;
	if (*ptr)
		ptr++;
	return (ptr);
}
