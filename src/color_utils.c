/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 05:39:16 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/27 05:39:28 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color_gradient(int start_color, int end_color, int position, int length)
{
	t_color	start_rgb;
	t_color	end_rgb;
	t_color	new_rgb;
	int		pixel;

	if (length == 0)
		return (end_color);
	start_rgb.r = (start_color >> 16) & 0xFF;
	start_rgb.g = (start_color >> 8) & 0xFF;
	start_rgb.b = start_color & 0xFF;
	end_rgb.r = (end_color >> 16) & 0xFF;
	end_rgb.g = (end_color >> 8) & 0xFF;
	end_rgb.b = end_color & 0xFF;
	new_rgb.r = start_rgb.r + ((end_rgb.r - start_rgb.r) * position / length);
	new_rgb.g = start_rgb.g + ((end_rgb.g - start_rgb.g) * position / length);
	new_rgb.b = start_rgb.b + ((end_rgb.b - start_rgb.b) * position / length);
	pixel = (new_rgb.r << 24) | (new_rgb.g << 16) | (new_rgb.b << 8) | 0xFF;
	return (pixel);
}

void	set_default_color(int *color_ref, int z_val)
{
	int	new_z;

	new_z = z_val * 40;
	if (new_z == 0)
		return ;
	if (new_z > 255)
		new_z = 255;
	*color_ref = (new_z << 8) | 0x8A2BE2;
}

int	parse_hex_string(const char *hex_str)
{
	int	result;

	result = 0;
	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		hex_str += 2;
	while (*hex_str)
	{
		result *= 16;
		if (*hex_str >= '0' && *hex_str <= '9')
			result += *hex_str - '0';
		else if (*hex_str >= 'a' && *hex_str <= 'f')
			result += *hex_str - 'a' + 10;
		else if (*hex_str >= 'A' && *hex_str <= 'F')
			result += *hex_str - 'A' + 10;
		else
			break ;
		hex_str++;
	}
	return (result);
}
