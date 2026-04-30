/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_hex(char *str)
{
	int	result;
	int	digit;

	if (!str || !*str)
		return (-1);
	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			digit = *str - 'A' + 10;
		else
			return (-1);
		result = result * 16 + digit;
		str++;
	}
	return (result);
}

int	parse_token(char *token, int *z, int *color)
{
	char	*comma;
	char	*hex_start;

	*z = ft_atoi(token);
	comma = ft_strchr(token, ',');
	if (comma)
	{
		if (comma[1] != '0' || (comma[2] != 'x' && comma[2] != 'X'))
			return (-1);
		hex_start = comma + 3;
		*color = parse_hex(hex_start);
		if (*color < 0)
			return (-1);
	}
	return (0);
}
