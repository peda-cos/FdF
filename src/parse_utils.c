/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
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

	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			digit = *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			digit = *str - 'a' + 10;
		else
			digit = *str - 'A' + 10;
		result = result * 16 + digit;
		str++;
	}
	return (result);
}

void	parse_token(char *token, int *z, int *color)
{
	char	*comma;
	char	*hex_start;

	comma = ft_strchr(token, ',');
	if (comma)
	{
		*z = ft_atoi(token);
		hex_start = comma + 3;
		*color = parse_hex(hex_start);
	}
	else
		*z = ft_atoi(token);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	exit_error(char *msg, t_fdf *fdf)
{
	ft_putstr_fd(msg, 2);
	if (fdf)
		cleanup_fdf(fdf);
	exit(1);
}
