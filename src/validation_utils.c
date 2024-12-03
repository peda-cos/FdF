/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 22:03:51 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/02 22:47:55 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

uint8_t	check_range(char *number, char *min, char *max)
{
	uint8_t	number_length;
	uint8_t	index;

	number_length = ft_strlen(number);
	if ((number_length > 6) || (number_length > 5 && number[0] != '-'))
		return (0);
	index = 0;
	while (number[index] != '\0' && number_length == 5 && number[0] != '-')
	{
		if (number[index] < max[index])
			return (1);
		if (number[index] > max[index])
			return (0);
		index++;
	}
	index = 1;
	while (number[index] != '\0' && number_length == 6 && number[0] == '-')
	{
		if (number[index] < min[index])
			return (1);
		if (number[index] > min[index])
			return (0);
		index++;
	}
	return (1);
}

uint8_t	is_numeric_string(char *string)
{
	uint8_t	index;

	index = 0;
	if (string[0] == '-')
		index = 1;
	if (!ft_isdigit(string[index]))
		return (0);
	while (string[index] != '\0')
	{
		if (!ft_isdigit(string[index]))
			return (0);
		index++;
	}
	return (1);
}

void	validate_map_value(char *value, t_fdf *fdf)
{
	uint8_t	index;

	index = 0;
	while (value[index])
	{
		if (value[index] == ',')
			value[index] = '\0';
		else
			index++;
	}
	if (!is_numeric_string(value) || (value[0] == '0' && value[1] != '\0'))
	{
		ft_putstr_fd("Map Error: Value is invalid: ", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("\nAllowed characters: digits and -\n", 2);
		clean_exit("Leading zeros are not allowed", fdf);
	}
	if (!check_range(value, "-20000", "20000"))
	{
		ft_putstr_fd("Map Error: Value out of range: ", 2);
		ft_putstr_fd(value, 2);
		clean_exit("\nAllowed range: -20000 to 20000", fdf);
	}
}