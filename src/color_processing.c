/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:58:18 by peda-cos          #+#    #+#             */
/*   Updated: 2024/12/29 15:34:26 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	linear_interpolation(int start, int end, float ratio)
{
	return (start * (1 - ratio) + end * ratio);
}

uint32_t	interpolate_color(t_point start, t_point end,
		t_bresenham bresenham_state)
{
	int		red;
	int		green;
	int		blue;
	int		alpha;
	float	ratio;

	if (start.color == end.color)
		return (start.color);
	ratio = (float)(start.x - bresenham_state.initial_x) / (float)(end.x
			- bresenham_state.initial_x);
	red = linear_interpolation((start.color >> 24) & 0xFF,
			(end.color >> 24) & 0xFF, ratio);
	green = linear_interpolation((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, ratio);
	blue = linear_interpolation((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, ratio);
	alpha = linear_interpolation(start.color & 0xFF, end.color & 0xFF, ratio);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

uint32_t	convert_hex_to_rgba(unsigned int hex_value)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (hex_value >> 24) & 0xFF;
	green = (hex_value >> 16) & 0xFF;
	blue = (hex_value >> 8) & 0xFF;
	alpha = hex_value & 0xFF;
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

uint32_t	parse_color(char *line)
{
	char		**tokens;
	uint32_t	color_value;

	if (ft_strchr(line, ',') != NULL)
	{
		tokens = ft_split(line, ',');
		if (tokens && tokens[1])
		{
			color_value = ft_atoi_base(tokens[1], "0123456789abcdef");
			color_value = (color_value << 8) | 0xff;
		}
		else
			color_value = 0;
		color_value = convert_hex_to_rgba(color_value);
		free_string_array(tokens);
	}
	else
		color_value = convert_hex_to_rgba(0xebdbb2);
	return (color_value);
}
