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
	int	len;

	if (!str || !*str)
		return (-1);
	result = 0;
	len = 0;
	while (str[len])
	{
		if (len >= 6)
			return (-1);
		if (str[len] >= '0' && str[len] <= '9')
			digit = str[len] - '0';
		else if (str[len] >= 'a' && str[len] <= 'f')
			digit = str[len] - 'a' + 10;
		else if (str[len] >= 'A' && str[len] <= 'F')
			digit = str[len] - 'A' + 10;
		else
			return (-1);
		result = result * 16 + digit;
		len++;
	}
	return (result);
}

int	parse_token(char *token, int *z, int *color)
{
	char	*comma;

	*z = ft_atoi(token);
	comma = ft_strchr(token, ',');
	if (comma)
	{
		if (comma[1] != '0' || (comma[2] != 'x' && comma[2] != 'X'))
			return (-1);
		*color = parse_hex(comma + 3);
		if (*color < 0)
			return (-1);
	}
	else
		*color = -1;
	return (0);
}
